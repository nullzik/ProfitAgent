#include "application/services/ActivityService.h"
#include "application/database/Database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include <QDateTime>
#include <QDebug>
#include <QUuid>

namespace application {

static QString classifyFinanceEventType(int type, const QString& category)
{
    const QString c = category.trimmed();
    if (c.startsWith(QStringLiteral("Продажи стол"))) return QStringLiteral("Продажа");
    if (c.startsWith(QStringLiteral("Поставка:"))) return QStringLiteral("Поставка");
    if (c.startsWith(QStringLiteral("Списание:"))) return QStringLiteral("Списание");
    if (c.startsWith(QStringLiteral("Зарплата:"))) return QStringLiteral("Зарплата");
    if (c.startsWith(QStringLiteral("Премия:"))) return QStringLiteral("Премия");
    if (c.startsWith(QStringLiteral("Штраф:"))) return QStringLiteral("Штраф");
    return (type == 1) ? QStringLiteral("Доход") : QStringLiteral("Расход");
}

bool ActivityService::logEvent(const QString& eventType,
                              const QString& title,
                              const QString& sender,
                              const QString& details,
                              const QString& source,
                              const QString& sourceId,
                              qint64 createdAtMs,
                              qint64 amountMinorUnits,
                              bool hasAmount)
{
    if (eventType.trimmed().isEmpty() || title.trimmed().isEmpty()) {
        return false;
    }

    QSqlQuery q(Database::connection());
    const qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    const qint64 ts = (createdAtMs >= 0) ? createdAtMs : now;

    const QString src = source.trimmed();
    QString srcId = sourceId.trimmed();
    if (!src.isEmpty() && srcId.isEmpty()) {
        srcId = QUuid::createUuid().toString(QUuid::Id128);
    }

    q.prepare(QStringLiteral(
        "INSERT OR IGNORE INTO activity_log "
        "(event_type, title, sender, details, created_at, source, source_id, amount_minor_units, has_amount) "
        "VALUES (:event_type, :title, :sender, :details, :created_at, :source, :source_id, :amount, :has_amount)"));
    q.bindValue(QStringLiteral(":event_type"), eventType.trimmed());
    q.bindValue(QStringLiteral(":title"), title.trimmed());
    q.bindValue(QStringLiteral(":sender"), sender.trimmed());
    q.bindValue(QStringLiteral(":details"), details.trimmed());
    q.bindValue(QStringLiteral(":created_at"), ts);
    q.bindValue(QStringLiteral(":source"), src.isEmpty() ? QVariant() : QVariant(src));
    q.bindValue(QStringLiteral(":source_id"), srcId.isEmpty() ? QVariant() : QVariant(srcId));
    q.bindValue(QStringLiteral(":amount"), static_cast<qint64>(amountMinorUnits));
    q.bindValue(QStringLiteral(":has_amount"), hasAmount ? 1 : 0);

    if (!q.exec()) {
        qWarning() << "ActivityService::logEvent failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ActivityService::logFinancialTransaction(int id,
                                              int type,
                                              qint64 amountMinorUnits,
                                              const QString& category,
                                              const QString& description,
                                              qint64 createdAtMs)
{
    const QString c = category.trimmed();
    // Продажи стола и поставки уже пишутся в activity через UI/доменный поток.
    // Для зарплат/премий/штрафов лог ведём здесь, чтобы не терять финансовые операции.
    if (c.startsWith(QStringLiteral("Поставка:"))
        || c.startsWith(QStringLiteral("Продажи стол"))) {
        return true;
    }

    const QString eventType = classifyFinanceEventType(type, category);
    const QString title = c;
    QString sender = QStringLiteral("Финансы");
    if (c.startsWith(QStringLiteral("Премия:"))) {
        sender = QStringLiteral("Менеджер / Финансы");
    }
    const QString details = description.trimmed();
    return logEvent(eventType,
                    title.isEmpty() ? QStringLiteral("Финансовая операция") : title,
                    sender,
                    details,
                    QStringLiteral("financial_transactions"),
                    QString::number(id),
                    createdAtMs,
                    amountMinorUnits,
                    true);
}

QVariantList ActivityService::getRecentEvents(int limit, int offset, const QString& typeFilter)
{
    QVariantList result;
    if (limit <= 0) return result;
    if (offset < 0) offset = 0;

    QSqlQuery q(Database::connection());
    QString sql = QStringLiteral(
        "SELECT event_type, title, sender, details, created_at, has_amount, amount_minor_units "
        "FROM activity_log ");
    if (!typeFilter.trimmed().isEmpty()) {
        sql += QStringLiteral("WHERE event_type = :filter ");
    }
    sql += QStringLiteral("ORDER BY created_at DESC, id DESC "
                          "LIMIT :limit OFFSET :offset");
    q.prepare(sql);
    if (!typeFilter.trimmed().isEmpty()) {
        q.bindValue(QStringLiteral(":filter"), typeFilter.trimmed());
    }
    q.bindValue(QStringLiteral(":limit"), limit);
    q.bindValue(QStringLiteral(":offset"), offset);

    if (!q.exec()) {
        qWarning() << "ActivityService::getRecentEvents failed:" << q.lastError().text();
        return result;
    }

    while (q.next()) {
        QVariantMap m;
        m.insert(QStringLiteral("eventType"), q.value(0).toString());
        m.insert(QStringLiteral("title"), q.value(1).toString());
        m.insert(QStringLiteral("sender"), q.value(2).toString());
        m.insert(QStringLiteral("details"), q.value(3).toString());
        const qint64 ms = q.value(4).toLongLong();
        m.insert(QStringLiteral("createdAtMs"), ms);
        m.insert(QStringLiteral("createdAtFormatted"),
                 QDateTime::fromMSecsSinceEpoch(ms).toString(QStringLiteral("dd.MM.yyyy HH:mm")));
        const bool hasAmount = q.value(5).toInt() != 0;
        const qint64 amountMinor = q.value(6).toLongLong();
        m.insert(QStringLiteral("hasAmount"), hasAmount);
        m.insert(QStringLiteral("amountRubles"), static_cast<double>(amountMinor) / 100.0);
        result.append(m);
    }

    return result;
}

int ActivityService::getTotalCount(const QString& typeFilter)
{
    QSqlQuery q(Database::connection());
    if (typeFilter.trimmed().isEmpty()) {
        if (!q.exec(QStringLiteral("SELECT COUNT(*) FROM activity_log")) || !q.next()) {
            return 0;
        }
    } else {
        q.prepare(QStringLiteral("SELECT COUNT(*) FROM activity_log WHERE event_type = :filter"));
        q.bindValue(QStringLiteral(":filter"), typeFilter.trimmed());
        if (!q.exec() || !q.next()) {
            return 0;
        }
    }
    return q.value(0).toInt();
}

} // namespace application

