#include "application/services/EmployeeService.h"
#include "application/database/Database.h"
#include "application/services/FinanceService.h"
#include "application/services/ActivityService.h"

#include <QSqlQuery>
#include <QCryptographicHash>
#include <cmath>
#include <QSqlError>
#include <QUuid>
#include <QVariantMap>
#include <QDateTime>
#include <QDebug>

namespace application {

static QStringList roleNames() {
    return {
        QStringLiteral("Официант"), QStringLiteral("Повар"), QStringLiteral("Менеджер"),
        QStringLiteral("Директор"), QStringLiteral("Кассир"), QStringLiteral("Другое")
    };
}

// Map employee role (0-5) to system login role (0=Waiter, 1=Chef, 2=Manager)
static int employeeRoleToSystemRole(int employeeRole) {
    if (employeeRole <= 2) return employeeRole;
    if (employeeRole == 3) return 2;  // Director -> Manager
    if (employeeRole == 4) return 0;  // Cashier -> Waiter
    return 0;  // Other -> Waiter
}

QVariantList EmployeeService::getAllEmployees()
{
    QVariantList result;
    QSqlQuery q(Database::connection());

    if (!q.exec(QStringLiteral(
        "SELECT e.id, e.full_name, e.age, e.phone, e.address, e.role, e.hourly_rate, e.worked_hours, e.salary_balance, u.login "
        "FROM employees e LEFT JOIN users u ON u.employee_id = e.id ORDER BY e.full_name"))) {
        qWarning() << "getAllEmployees failed:" << q.lastError().text();
        return result;
    }

    const QStringList rn = roleNames();
    while (q.next()) {
        QVariantMap m;
        m.insert(QStringLiteral("id"), q.value(0).toString());
        m.insert(QStringLiteral("fullName"), q.value(1).toString());
        m.insert(QStringLiteral("age"), q.value(2).toInt());
        m.insert(QStringLiteral("phone"), q.value(3).toString());
        m.insert(QStringLiteral("address"), q.value(4).toString());
        const int r = q.value(5).toInt();
        m.insert(QStringLiteral("role"), r);
        m.insert(QStringLiteral("roleName"), rn.value(r, QStringLiteral("Другое")));
        m.insert(QStringLiteral("hourlyRate"), q.value(6).toInt() / 100.0);
        m.insert(QStringLiteral("workedHours"), q.value(7).toDouble());
        m.insert(QStringLiteral("salaryBalance"), q.value(8).toDouble() / 100.0);
        m.insert(QStringLiteral("login"), q.value(9).toString());
        result.append(m);
    }

    return result;
}

QVariantMap EmployeeService::getEmployeeById(const QString& id)
{
    QVariantMap result;
    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT e.id, e.full_name, e.age, e.phone, e.address, e.role, e.hourly_rate, e.worked_hours, e.salary_balance, u.login "
        "FROM employees e LEFT JOIN users u ON u.employee_id = e.id WHERE e.id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    if (!q.exec() || !q.next()) return result;

    const QStringList rn = roleNames();
    result.insert(QStringLiteral("id"), q.value(0).toString());
    result.insert(QStringLiteral("fullName"), q.value(1).toString());
    result.insert(QStringLiteral("age"), q.value(2).toInt());
    result.insert(QStringLiteral("phone"), q.value(3).toString());
    result.insert(QStringLiteral("address"), q.value(4).toString());
    const int r = q.value(5).toInt();
    result.insert(QStringLiteral("role"), r);
    result.insert(QStringLiteral("roleName"), rn.value(r, QStringLiteral("Другое")));
    result.insert(QStringLiteral("hourlyRate"), q.value(6).toInt() / 100.0);
    result.insert(QStringLiteral("workedHours"), q.value(7).toDouble());
    result.insert(QStringLiteral("salaryBalance"), q.value(8).toDouble() / 100.0);
    result.insert(QStringLiteral("login"), q.value(9).toString());
    return result;
}

bool EmployeeService::createEmployee(const QString& fullName, int age, const QString& phone,
                                     const QString& address, int role, double hourlyRate,
                                     const QString& login, const QString& password)
{
    if (fullName.trimmed().isEmpty()) {
        qWarning() << "createEmployee: fullName is empty";
        return false;
    }

    const QString id = QUuid::createUuid().toString(QUuid::Id128);
    const int hourlyRateMinor = static_cast<int>(std::llround(hourlyRate * 100.0));

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "INSERT INTO employees (id, full_name, age, phone, address, role, hourly_rate, worked_hours, salary_balance) "
        "VALUES (:id, :full_name, :age, :phone, :address, :role, :hourly_rate, 0, 0)"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":full_name"), fullName.trimmed());
    q.bindValue(QStringLiteral(":age"), age);
    q.bindValue(QStringLiteral(":phone"), phone.trimmed());
    q.bindValue(QStringLiteral(":address"), address.trimmed());
    q.bindValue(QStringLiteral(":role"), role);
    q.bindValue(QStringLiteral(":hourly_rate"), hourlyRateMinor);

    if (!q.exec()) {
        qWarning() << "createEmployee failed:" << q.lastError().text();
        return false;
    }

    if (!login.trimmed().isEmpty() && !password.isEmpty()) {
        const QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
        const int systemRole = employeeRoleToSystemRole(role);
        QSqlQuery u(Database::connection());
        u.prepare(QStringLiteral(
            "INSERT INTO users (login, password_hash, role, employee_id) VALUES (:login, :hash, :role, :emp_id)"));
        u.bindValue(QStringLiteral(":login"), login.trimmed());
        u.bindValue(QStringLiteral(":hash"), QString::fromUtf8(hash));
        u.bindValue(QStringLiteral(":role"), systemRole);
        u.bindValue(QStringLiteral(":emp_id"), id);
        if (!u.exec()) {
            qWarning() << "createEmployee: create user failed:" << u.lastError().text();
        }
    }

    ActivityService::logEvent(
        QStringLiteral("Сотрудники"),
        QStringLiteral("Добавлен сотрудник: %1").arg(fullName.trimmed()),
        QStringLiteral("Сотрудники"),
        QStringLiteral("Роль: %1").arg(roleNames().value(role, QStringLiteral("Другое"))));

    return true;
}

bool EmployeeService::updateEmployee(const QString& id, const QString& fullName, int age, const QString& phone,
                                     const QString& address, int role, double hourlyRate,
                                     const QString& login, const QString& password)
{
    if (fullName.trimmed().isEmpty()) {
        qWarning() << "updateEmployee: fullName is empty";
        return false;
    }

    const int hourlyRateMinor = static_cast<int>(std::llround(hourlyRate * 100.0));

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "UPDATE employees SET full_name = :full_name, age = :age, phone = :phone, address = :address, role = :role, hourly_rate = :hourly_rate "
        "WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":full_name"), fullName.trimmed());
    q.bindValue(QStringLiteral(":age"), age);
    q.bindValue(QStringLiteral(":phone"), phone.trimmed());
    q.bindValue(QStringLiteral(":address"), address.trimmed());
    q.bindValue(QStringLiteral(":role"), role);
    q.bindValue(QStringLiteral(":hourly_rate"), hourlyRateMinor);

    if (!q.exec()) {
        qWarning() << "updateEmployee failed:" << q.lastError().text();
        return false;
    }

    QSqlQuery checkUser(Database::connection());
    checkUser.prepare(QStringLiteral("SELECT id FROM users WHERE employee_id = :id"));
    checkUser.bindValue(QStringLiteral(":id"), id);
    checkUser.exec();

    if (login.trimmed().isEmpty()) {
        if (password.isEmpty()) return true;
        if (checkUser.next()) {
            QSqlQuery upd(Database::connection());
            upd.prepare(QStringLiteral("UPDATE users SET password_hash = :hash WHERE employee_id = :id"));
            upd.bindValue(QStringLiteral(":hash"), QString::fromUtf8(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex()));
            upd.bindValue(QStringLiteral(":id"), id);
            upd.exec();
        }
        return true;
    }

    const QByteArray hash = password.isEmpty() ? QByteArray() : QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    const int systemRole = employeeRoleToSystemRole(role);

    if (checkUser.next()) {
        QSqlQuery upd(Database::connection());
        if (password.isEmpty()) {
            upd.prepare(QStringLiteral("UPDATE users SET login = :login, role = :role WHERE employee_id = :id"));
            upd.bindValue(QStringLiteral(":login"), login.trimmed());
            upd.bindValue(QStringLiteral(":role"), systemRole);
            upd.bindValue(QStringLiteral(":id"), id);
        } else {
            upd.prepare(QStringLiteral("UPDATE users SET login = :login, password_hash = :hash, role = :role WHERE employee_id = :id"));
            upd.bindValue(QStringLiteral(":login"), login.trimmed());
            upd.bindValue(QStringLiteral(":hash"), QString::fromUtf8(hash));
            upd.bindValue(QStringLiteral(":role"), systemRole);
            upd.bindValue(QStringLiteral(":id"), id);
        }
        upd.exec();
    } else {
        if (password.isEmpty()) return true;
        QSqlQuery ins(Database::connection());
        ins.prepare(QStringLiteral(
            "INSERT INTO users (login, password_hash, role, employee_id) VALUES (:login, :hash, :role, :emp_id)"));
        ins.bindValue(QStringLiteral(":login"), login.trimmed());
        ins.bindValue(QStringLiteral(":hash"), QString::fromUtf8(hash));
        ins.bindValue(QStringLiteral(":role"), systemRole);
        ins.bindValue(QStringLiteral(":emp_id"), id);
        ins.exec();
    }

    return true;
}

bool EmployeeService::adjustSalaryBalance(const QString& id, double deltaRubles)
{
    QSqlQuery q(Database::connection());
    const int deltaMinor = static_cast<int>(std::llround(deltaRubles * 100.0));

    q.prepare(QStringLiteral(
        "UPDATE employees "
        "SET salary_balance = salary_balance + :delta "
        "WHERE id = :id"));
    q.bindValue(QStringLiteral(":delta"), deltaMinor);
    q.bindValue(QStringLiteral(":id"), id);

    if (!q.exec()) {
        qWarning() << "adjustSalaryBalance failed:" << q.lastError().text();
        return false;
    }

    if (q.numRowsAffected() <= 0) {
        return false;
    }

    // Финансовый учёт: премии и штрафы
    if (deltaRubles != 0.0) {
        const QVariantMap emp = EmployeeService::getEmployeeById(id);
        const QString fullName = emp.value(QStringLiteral("fullName")).toString();
        const double amount = std::abs(deltaRubles);

        if (deltaRubles > 0.0) {
            // Премия сотруднику — расход
            const QString category = QStringLiteral("Премия: %1").arg(fullName);
            const QString description = QStringLiteral("Премия сотруднику %1").arg(fullName);
            FinanceService::addTransaction(FinanceService::Expense, amount, category, description);
        } else {
            // Штраф сотруднику — учитываем как доход
            const QString category = QStringLiteral("Штраф: %1").arg(fullName);
            const QString description = QStringLiteral("Штраф сотруднику %1").arg(fullName);
            FinanceService::addTransaction(FinanceService::Income, amount, category, description);
        }
    }

    return true;
}

bool EmployeeService::deleteEmployee(const QString& id)
{
    if (id.trimmed().isEmpty()) {
        return false;
    }

    const QVariantMap emp = EmployeeService::getEmployeeById(id);
    const QString fullName = emp.value(QStringLiteral("fullName")).toString();

    QSqlDatabase db = Database::connection();
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery q(db);

    // Delete related user account
    q.prepare(QStringLiteral("DELETE FROM users WHERE employee_id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    if (!q.exec()) {
        qWarning() << "deleteEmployee: delete users failed:" << q.lastError().text();
        return false;
    }

    // Delete related shifts
    QSqlQuery qs(db);
    qs.prepare(QStringLiteral("DELETE FROM shifts WHERE employee_id = :id"));
    qs.bindValue(QStringLiteral(":id"), id);
    if (!qs.exec()) {
        qWarning() << "deleteEmployee: delete shifts failed:" << qs.lastError().text();
        return false;
    }

    // Finally delete employee
    QSqlQuery qe(db);
    qe.prepare(QStringLiteral("DELETE FROM employees WHERE id = :id"));
    qe.bindValue(QStringLiteral(":id"), id);
    if (!qe.exec()) {
        qWarning() << "deleteEmployee: delete employee failed:" << qe.lastError().text();
        return false;
    }

    const bool ok = qe.numRowsAffected() > 0;
    if (ok) {
        ActivityService::logEvent(
            QStringLiteral("Сотрудники"),
            QStringLiteral("Удалён сотрудник: %1").arg(fullName.isEmpty() ? id : fullName),
            QStringLiteral("Сотрудники"),
            QStringLiteral("ID: %1").arg(id.trimmed()));
    }
    return ok;
}

} // namespace application
