#include "application/services/FinanceService.h"
#include "application/database/Database.h"
#include "application/services/ActivityService.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include <QDateTime>
#include <QDebug>
#include <cmath>

namespace application {

QVariantList FinanceService::getAllTransactions()
{
    return getTransactionsByType(0);
}

QVariantList FinanceService::getTransactionsByType(int type)
{
    QVariantList result;
    QSqlQuery q(Database::connection());

    if (type == Income || type == Expense) {
        q.prepare(QStringLiteral(
            "SELECT id, type, amount_minor_units, category, description, created_at "
            "FROM financial_transactions WHERE type = :type "
            "ORDER BY created_at DESC"));
        q.bindValue(QStringLiteral(":type"), type);
    } else {
        q.prepare(QStringLiteral(
            "SELECT id, type, amount_minor_units, category, description, created_at "
            "FROM financial_transactions "
            "ORDER BY created_at DESC"));
    }

    if (!q.exec()) {
        qWarning() << "getTransactionsByType failed:" << q.lastError().text();
        return result;
    }

    while (q.next()) {
        QVariantMap m;
        m.insert(QStringLiteral("id"), q.value(0).toInt());
        m.insert(QStringLiteral("type"), q.value(1).toInt());
        const qint64 minor = q.value(2).toLongLong();
        m.insert(QStringLiteral("amountRubles"), minor / 100.0);
        m.insert(QStringLiteral("category"), q.value(3).toString());
        m.insert(QStringLiteral("description"), q.value(4).toString());
        const qint64 ms = q.value(5).toLongLong();
        m.insert(QStringLiteral("createdAt"), QDateTime::fromMSecsSinceEpoch(ms).toString(Qt::ISODate));
        m.insert(QStringLiteral("createdAtFormatted"), QDateTime::fromMSecsSinceEpoch(ms).toString(QStringLiteral("dd.MM.yyyy HH:mm")));
        result.append(m);
    }

    return result;
}

bool FinanceService::addTransaction(int type, double amountRubles, const QString& category)
{
    return addTransaction(type, amountRubles, category, QString());
}

bool FinanceService::addTransaction(int type, double amountRubles, const QString& category, const QString& description)
{
    if (type != Income && type != Expense) {
        qWarning() << "addTransaction: invalid type" << type;
        return false;
    }
    if (category.trimmed().isEmpty()) {
        qWarning() << "addTransaction: category is empty";
        return false;
    }

    const qint64 minor = static_cast<qint64>(std::llround(amountRubles * 100.0));
    const qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "INSERT INTO financial_transactions (type, amount_minor_units, category, description, created_at) "
        "VALUES (:type, :amount, :category, :desc, :created_at)"));
    q.bindValue(QStringLiteral(":type"), type);
    q.bindValue(QStringLiteral(":amount"), minor);
    q.bindValue(QStringLiteral(":category"), category.trimmed());
    q.bindValue(QStringLiteral(":desc"), description.trimmed());
    q.bindValue(QStringLiteral(":created_at"), now);

    if (!q.exec()) {
        qWarning() << "addTransaction failed:" << q.lastError().text();
        return false;
    }

    const QVariant idVar = q.lastInsertId();
    if (idVar.isValid()) {
        const int txId = idVar.toInt();
        ActivityService::logFinancialTransaction(
            txId,
            type,
            minor,
            category.trimmed(),
            description.trimmed(),
            now);
    }
    return true;
}

bool FinanceService::updateTransaction(int id, int type, double amountRubles, const QString& category, const QString& description)
{
    if (type != Income && type != Expense) return false;
    if (category.trimmed().isEmpty()) return false;

    const qint64 minor = static_cast<qint64>(std::llround(amountRubles * 100.0));

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "UPDATE financial_transactions SET type=:type, amount_minor_units=:amount, category=:category, description=:desc WHERE id=:id"));
    q.bindValue(QStringLiteral(":type"), type);
    q.bindValue(QStringLiteral(":amount"), minor);
    q.bindValue(QStringLiteral(":category"), category.trimmed());
    q.bindValue(QStringLiteral(":desc"), description.trimmed());
    q.bindValue(QStringLiteral(":id"), id);

    if (!q.exec()) {
        qWarning() << "updateTransaction failed:" << q.lastError().text();
        return false;
    }
    return q.numRowsAffected() > 0;
}

bool FinanceService::deleteTransaction(int id)
{
    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral("DELETE FROM financial_transactions WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    if (!q.exec()) {
        qWarning() << "deleteTransaction failed:" << q.lastError().text();
        return false;
    }
    return q.numRowsAffected() > 0;
}

double FinanceService::getTotalIncome()
{
    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT COALESCE(SUM(amount_minor_units), 0) FROM financial_transactions WHERE type = 1"));
    if (!q.exec() || !q.next()) return 0.0;
    return q.value(0).toLongLong() / 100.0;
}

double FinanceService::getTotalExpenses()
{
    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT COALESCE(SUM(amount_minor_units), 0) FROM financial_transactions WHERE type = 2"));
    if (!q.exec() || !q.next()) return 0.0;
    return q.value(0).toLongLong() / 100.0;
}

double FinanceService::getProfit()
{
    return getTotalIncome() - getTotalExpenses();
}

static void calcWindowMs(int days, int offsetDays, qint64& fromMs, qint64& toMs)
{
    if (days <= 0) days = 1;
    if (offsetDays < 0) offsetDays = 0;
    const qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    const qint64 dayMs = 24LL * 60LL * 60LL * 1000LL;
    toMs = now - static_cast<qint64>(offsetDays) * dayMs;
    fromMs = now - static_cast<qint64>(offsetDays + days) * dayMs;
}

double FinanceService::getSalesRevenueForDays(int days, int offsetDays)
{
    qint64 fromMs = 0, toMs = 0;
    calcWindowMs(days, offsetDays, fromMs, toMs);

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT COALESCE(SUM(amount_minor_units), 0) "
        "FROM financial_transactions "
        "WHERE type = 1 AND category LIKE 'Продажи стол%' "
        "AND created_at >= :from AND created_at < :to"));
    q.bindValue(QStringLiteral(":from"), fromMs);
    q.bindValue(QStringLiteral(":to"), toMs);
    if (!q.exec() || !q.next()) return 0.0;
    return q.value(0).toLongLong() / 100.0;
}

int FinanceService::getSalesCountForDays(int days, int offsetDays)
{
    qint64 fromMs = 0, toMs = 0;
    calcWindowMs(days, offsetDays, fromMs, toMs);

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT COUNT(*) "
        "FROM financial_transactions "
        "WHERE type = 1 AND category LIKE 'Продажи стол%' "
        "AND created_at >= :from AND created_at < :to"));
    q.bindValue(QStringLiteral(":from"), fromMs);
    q.bindValue(QStringLiteral(":to"), toMs);
    if (!q.exec() || !q.next()) return 0;
    return q.value(0).toInt();
}

double FinanceService::getNetProfitForDays(int days, int offsetDays)
{
    qint64 fromMs = 0, toMs = 0;
    calcWindowMs(days, offsetDays, fromMs, toMs);

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT "
        "(SELECT COALESCE(SUM(amount_minor_units), 0) FROM financial_transactions "
        " WHERE type = 1 AND created_at >= :from AND created_at < :to) - "
        "(SELECT COALESCE(SUM(amount_minor_units), 0) FROM financial_transactions "
        " WHERE type = 2 AND created_at >= :from AND created_at < :to)"));
    q.bindValue(QStringLiteral(":from"), fromMs);
    q.bindValue(QStringLiteral(":to"), toMs);
    if (!q.exec() || !q.next()) return 0.0;
    return q.value(0).toLongLong() / 100.0;
}

QVariantList FinanceService::getWaiterAggregates()
{
    QVariantList result;
    QSqlQuery q(Database::connection());

    // role = 0 -> официант
    if (!q.exec(QStringLiteral(
            "SELECT id, full_name, worked_hours, salary_balance "
            "FROM employees WHERE role = 0 ORDER BY full_name"))) {
        qWarning() << "getWaiterAggregates failed:" << q.lastError().text();
        return result;
    }

    while (q.next()) {
        QVariantMap m;
        m.insert(QStringLiteral("id"), q.value(0).toString());
        m.insert(QStringLiteral("fullName"), q.value(1).toString());
        m.insert(QStringLiteral("workedHours"), q.value(2).toDouble());
        m.insert(QStringLiteral("salaryRubles"), q.value(3).toInt() / 100.0);
        result.append(m);
    }

    return result;
}

} // namespace application
