#include "application/services/ShiftService.h"
#include "application/database/Database.h"
#include "application/services/EmployeeService.h"

#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimeZone>
#include <QUuid>
#include <QDebug>
#include <cmath>

namespace application {

QString ShiftService::openShift(const QString& employeeId)
{
    if (employeeId.isEmpty()) return QString();

    // Check if employee already has open shift
    QVariantMap existing = getOpenShiftForEmployee(employeeId);
    if (!existing.isEmpty()) return existing.value(QStringLiteral("id")).toString();

    const QString id = QUuid::createUuid().toString(QUuid::Id128);
    const qint64 now = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "INSERT INTO shifts (id, employee_id, opened_at, closed_at) "
        "VALUES (:id, :emp_id, :opened, NULL)"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":emp_id"), employeeId);
    q.bindValue(QStringLiteral(":opened"), now);

    if (!q.exec()) {
        qWarning() << "openShift failed:" << q.lastError().text();
        return QString();
    }
    return id;
}

QVariantMap ShiftService::getOpenShiftForEmployee(const QString& employeeId)
{
    QVariantMap result;
    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT id, employee_id, opened_at FROM shifts "
        "WHERE employee_id = :emp_id AND closed_at IS NULL ORDER BY opened_at DESC LIMIT 1"));
    q.bindValue(QStringLiteral(":emp_id"), employeeId);
    if (!q.exec() || !q.next()) return result;

    const qint64 openedMs = q.value(2).toLongLong();
    QDateTime opened = QDateTime::fromMSecsSinceEpoch(openedMs, QTimeZone::utc());
    result.insert(QStringLiteral("id"), q.value(0).toString());
    result.insert(QStringLiteral("employeeId"), q.value(1).toString());
    result.insert(QStringLiteral("openedAt"), opened.toString(Qt::ISODate));
    result.insert(QStringLiteral("openedAtLocal"), opened.toLocalTime().toString("dd.MM.yyyy HH:mm"));
    return result;
}

QVariantList ShiftService::getAllOpenShifts()
{
    QVariantList result;
    QSqlQuery q(Database::connection());
    if (!q.exec(QStringLiteral(
        "SELECT s.id, s.employee_id, s.opened_at, e.full_name "
        "FROM shifts s JOIN employees e ON e.id = s.employee_id "
        "WHERE s.closed_at IS NULL ORDER BY s.opened_at ASC"))) {
        qWarning() << "getAllOpenShifts failed:" << q.lastError().text();
        return result;
    }

    while (q.next()) {
        QVariantMap m;
        m.insert(QStringLiteral("id"), q.value(0).toString());
        m.insert(QStringLiteral("employeeId"), q.value(1).toString());
        const qint64 openedMs = q.value(2).toLongLong();
        QDateTime opened = QDateTime::fromMSecsSinceEpoch(openedMs, QTimeZone::utc());
        m.insert(QStringLiteral("openedAt"), opened.toString(Qt::ISODate));
        m.insert(QStringLiteral("openedAtLocal"), opened.toLocalTime().toString("dd.MM.yyyy HH:mm"));
        m.insert(QStringLiteral("employeeName"), q.value(3).toString());
        result.append(m);
    }
    return result;
}

bool ShiftService::closeShift(const QString& shiftId, const QDateTime& closedAtUtc)
{
    if (shiftId.isEmpty()) return false;

    QSqlQuery sel(Database::connection());
    sel.prepare(QStringLiteral(
        "SELECT employee_id, opened_at FROM shifts WHERE id = :id AND closed_at IS NULL"));
    sel.bindValue(QStringLiteral(":id"), shiftId);
    if (!sel.exec() || !sel.next()) return false;

    const QString employeeId = sel.value(0).toString();
    const qint64 openedMs = sel.value(1).toLongLong();
    const qint64 closedMs = closedAtUtc.toMSecsSinceEpoch();

    if (closedMs <= openedMs) return false;

    const double hours = (closedMs - openedMs) / 3600000.0;

    QVariantMap emp = EmployeeService::getEmployeeById(employeeId);
    const double hourlyRate = emp.value(QStringLiteral("hourlyRate")).toDouble();
    const double earnings = hours * hourlyRate;

    // Update shift
    QSqlQuery upd(Database::connection());
    upd.prepare(QStringLiteral(
        "UPDATE shifts SET closed_at = :closed WHERE id = :id"));
    upd.bindValue(QStringLiteral(":closed"), closedMs);
    upd.bindValue(QStringLiteral(":id"), shiftId);
    if (!upd.exec()) return false;

    // Update employee: worked_hours, salary_balance
    const int earningsMinor = static_cast<int>(std::llround(earnings * 100.0));
    QSqlQuery empUpd(Database::connection());
    empUpd.prepare(QStringLiteral(
        "UPDATE employees SET "
        "worked_hours = worked_hours + :hours, "
        "salary_balance = salary_balance + :earnings "
        "WHERE id = :id"));
    empUpd.bindValue(QStringLiteral(":hours"), hours);
    empUpd.bindValue(QStringLiteral(":earnings"), earningsMinor);
    empUpd.bindValue(QStringLiteral(":id"), employeeId);
    if (!empUpd.exec()) return false;

    return true;
}

} // namespace application
