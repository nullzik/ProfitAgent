#pragma once

#include <QString>
#include <QVariantList>

namespace application {

class ActivityService {
public:
    // Writes an event to activity_log (INSERT OR IGNORE if source/sourceId already exists).
    static bool logEvent(const QString& eventType,
                         const QString& title,
                         const QString& sender,
                         const QString& details = QString(),
                         const QString& source = QString(),
                         const QString& sourceId = QString(),
                         qint64 createdAtMs = -1,
                         qint64 amountMinorUnits = 0,
                         bool hasAmount = false);

    // Convenience for financial_transactions backfill/live inserts.
    static bool logFinancialTransaction(int id,
                                        int type,
                                        qint64 amountMinorUnits,
                                        const QString& category,
                                        const QString& description,
                                        qint64 createdAtMs);

    // Returns latest events (QVariantMap: eventType,title,sender,details,createdAtMs,createdAtFormatted,hasAmount,amountRubles).
    // If typeFilter is not empty, only events with matching event_type are returned.
    static QVariantList getRecentEvents(int limit, int offset = 0, const QString& typeFilter = QString());

    // Returns total count of events (optionally filtered by event_type).
    static int getTotalCount(const QString& typeFilter = QString());
};

} // namespace application

