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
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
    + "/profitagent.db";
    QDir().mkpath(QFileInfo(dbPath).absolutePath());

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Database open failed:" << db.lastError().text();
        return false;
    }

    QSqlQuery q;
    // users: login, password_hash, role (0=Waiter, 1=Chef, 2=Manager), employee_id (link to employees)
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

    // warehouse_products: reference data for products
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS warehouse_products ("
        "id TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "unit INTEGER NOT NULL,"
        "is_in_stop_list INTEGER NOT NULL DEFAULT 0"
        ")"))) {
        qWarning() << "Create warehouse_products table failed:" << q.lastError().text();
        return false;
    }

    // warehouse_batches: stock batches for FIFO and cost
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS warehouse_batches ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "product_id TEXT NOT NULL,"
        "quantity REAL NOT NULL,"
        "purchase_price_minor_units INTEGER NOT NULL,"
        "created_at INTEGER NOT NULL,"
        "FOREIGN KEY(product_id) REFERENCES warehouse_products(id)"
        ")"))) {
        qWarning() << "Create warehouse_batches table failed:" << q.lastError().text();
        return false;
    }

    // menu_dishes: menu items
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS menu_dishes ("
        "id TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "sale_price_minor_units INTEGER NOT NULL,"
        "recipe_id TEXT NOT NULL,"
        "is_available INTEGER NOT NULL DEFAULT 1"
        ")"))) {
        qWarning() << "Create menu_dishes table failed:" << q.lastError().text();
        return false;
    }

    // shifts: employee shifts (opened_at/closed_at in milliseconds since epoch)
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS shifts ("
        "id TEXT PRIMARY KEY,"
        "employee_id TEXT NOT NULL,"
        "opened_at INTEGER NOT NULL,"
        "closed_at INTEGER,"
        "FOREIGN KEY(employee_id) REFERENCES employees(id)"
        ")"))) {
        qWarning() << "Create shifts table failed:" << q.lastError().text();
        return false;
    }

    // menu_recipe_ingredients: many-to-one recipe -> ingredients
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS menu_recipe_ingredients ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "recipe_id TEXT NOT NULL,"
        "product_id TEXT NOT NULL,"
        "quantity REAL NOT NULL,"
        "quantity_unit INTEGER NOT NULL DEFAULT 1,"
        "FOREIGN KEY(product_id) REFERENCES warehouse_products(id)"
        ")"))) {
        qWarning() << "Create menu_recipe_ingredients table failed:" << q.lastError().text();
        return false;
    }
    // Migration: add quantity_unit for old DBs (0=kg, 1=g, 2=L)
    QSqlQuery checkCol;
    if (checkCol.exec(QStringLiteral(
            "SELECT COUNT(*) FROM pragma_table_info('menu_recipe_ingredients') WHERE name='quantity_unit'"))) {
        if (checkCol.next() && checkCol.value(0).toInt() == 0) {
            q.exec(QStringLiteral("ALTER TABLE menu_recipe_ingredients ADD COLUMN quantity_unit INTEGER DEFAULT 1"));
        }
    }

    // financial_transactions: income/expense entries (type: 1=income, 2=expense)
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS financial_transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "type INTEGER NOT NULL,"
        "amount_minor_units INTEGER NOT NULL,"
        "category TEXT NOT NULL,"
        "description TEXT,"
        "created_at INTEGER NOT NULL"
        ")"))) {
        qWarning() << "Create financial_transactions table failed:" << q.lastError().text();
        return false;
    }

    // activity_log: unified stream of recent operations (includes financial_transactions backfill + domain events)
    if (!q.exec(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS activity_log ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "event_type TEXT NOT NULL,"
        "title TEXT NOT NULL,"
        "sender TEXT,"
        "details TEXT,"
        "created_at INTEGER NOT NULL,"
        "source TEXT,"
        "source_id TEXT,"
        "amount_minor_units INTEGER DEFAULT 0,"
        "has_amount INTEGER NOT NULL DEFAULT 0,"
        "UNIQUE(source, source_id)"
        ")"))) {
        qWarning() << "Create activity_log table failed:" << q.lastError().text();
        return false;
    }

    q.exec(QStringLiteral("CREATE INDEX IF NOT EXISTS idx_activity_log_created_at ON activity_log(created_at DESC)"));

    // Backfill activity_log from existing financial_transactions (idempotent because of UNIQUE(source, source_id))
    q.exec(QStringLiteral(
        "INSERT OR IGNORE INTO activity_log "
        "(event_type, title, sender, details, created_at, source, source_id, amount_minor_units, has_amount) "
        "SELECT "
        "CASE "
        " WHEN category LIKE 'Продажи стол%' THEN 'Продажа' "
        " WHEN category LIKE 'Поставка:%' THEN 'Поставка' "
        " WHEN category LIKE 'Списание:%' THEN 'Списание' "
        " WHEN category LIKE 'Зарплата:%' THEN 'Зарплата' "
        " WHEN category LIKE 'Премия:%' THEN 'Премия' "
        " WHEN category LIKE 'Штраф:%' THEN 'Штраф' "
        " WHEN type = 1 THEN 'Доход' ELSE 'Расход' "
        "END, "
        "category, "
        "'Финансы', "
        "COALESCE(description, ''), "
        "created_at, "
        "'financial_transactions', "
        "CAST(id AS TEXT), "
        "amount_minor_units, "
        "1 "
        "FROM financial_transactions"));

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
