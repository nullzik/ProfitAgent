#include "application/database/Database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

namespace application {

bool Database::initialize(const QString& path)
{
    const QString dbPath = path.isEmpty()
        ? QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/profitagent.db")
        : path;

    QDir().mkpath(QFileInfo(dbPath).absolutePath());

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Database open failed:" << db.lastError().text();
        return false;
    }

    // users: login, password_hash, role (0=Waiter, 1=Chef, 2=Manager), employee_id (link to employees)
    QSqlQuery q;
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "login TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "role INTEGER NOT NULL DEFAULT 0,"
        "employee_id TEXT UNIQUE"
        ")"))) {
        qWarning() << "Create users table failed:" << q.lastError().text();
        return false;
    }
    // Migration: add employee_id to existing DBs created without it
    q.exec(QStringLiteral("ALTER TABLE users ADD COLUMN employee_id TEXT"));

    // employees: id, full_name, age, phone, address, role, hourly_rate, worked_hours, salary_balance
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS employees ("
        "id TEXT PRIMARY KEY,"
        "full_name TEXT NOT NULL,"
        "age INTEGER DEFAULT 0,"
        "phone TEXT,"
        "address TEXT,"
        "role INTEGER DEFAULT 0,"
        "hourly_rate INTEGER DEFAULT 0,"
        "worked_hours REAL DEFAULT 0,"
        "salary_balance INTEGER DEFAULT 0"
        ")"))) {
        qWarning() << "Create employees table failed:" << q.lastError().text();
        return false;
    }

    // Ensure default manager exists: hash of "manager" (same as AuthService)
    const QByteArray managerHash = QCryptographicHash::hash(
        QByteArrayLiteral("manager"), QCryptographicHash::Sha256).toHex();
    const QString hashStr = QString::fromUtf8(managerHash);

    QSqlQuery check(Database::connection());
    check.prepare(QStringLiteral("SELECT 1 FROM users WHERE login = 'manager' LIMIT 1"));
    if (check.exec() && check.next()) {
        // Update password in case it was wrong
        QSqlQuery upd(Database::connection());
        upd.prepare(QStringLiteral("UPDATE users SET password_hash = :hash WHERE login = 'manager'"));
        upd.bindValue(QStringLiteral(":hash"), hashStr);
        upd.exec();
    } else {
        QSqlQuery ins(Database::connection());
        ins.prepare(QStringLiteral(
            "INSERT INTO users (login, password_hash, role, employee_id) VALUES ('manager', :hash, 2, NULL)"));
        ins.bindValue(QStringLiteral(":hash"), hashStr);
        if (!ins.exec()) {
            qWarning() << "Insert default user failed:" << ins.lastError().text();
        }
    }

    return true;
}

QSqlDatabase Database::connection()
{
    return QSqlDatabase::database();
}

} // namespace application
