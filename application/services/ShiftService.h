#pragma once

#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QDateTime>

namespace application {

class ShiftService {
public:
    // Opens a shift for employee (opened_at = now). Returns shift id or empty on failure.
    static QString openShift(const QString& employeeId);

    // Returns open shift for employee (closed_at IS NULL), or empty map if none.
    static QVariantMap getOpenShiftForEmployee(const QString& employeeId);

    // Returns all open shifts (for manager). Each map: id, employee_id, employee_name, opened_at.
    static QVariantList getAllOpenShifts();

    // Closes shift: sets closed_at, adds hours*rate to salary_balance and worked_hours.
    // closedAtUtc - closing time.
    static bool closeShift(const QString& shiftId, const QDateTime& closedAtUtc);
};

} // namespace application
