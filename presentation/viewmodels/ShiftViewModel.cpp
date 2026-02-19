#include "ShiftViewModel.h"
#include "application/services/ShiftService.h"

#include <QDateTime>
#include <QDebug>

ShiftViewModel::ShiftViewModel(QObject *parent)
    : QObject(parent)
{
}

void ShiftViewModel::setCurrentEmployeeId(const QString& id)
{
    if (m_currentEmployeeId != id) {
        m_currentEmployeeId = id;
        refresh();
    }
}

void ShiftViewModel::refresh()
{
    if (!m_currentEmployeeId.isEmpty()) {
        m_myOpenShift = application::ShiftService::getOpenShiftForEmployee(m_currentEmployeeId);
        m_hasOpenShift = !m_myOpenShift.isEmpty();
        emit myOpenShiftChanged();
        emit hasOpenShiftChanged();
    }
    m_openShifts = application::ShiftService::getAllOpenShifts();
    emit openShiftsChanged();
}

bool ShiftViewModel::openShift()
{
    if (m_currentEmployeeId.isEmpty()) {
        setLastError(tr("Не задан сотрудник"));
        return false;
    }
    const QString id = application::ShiftService::openShift(m_currentEmployeeId);
    if (id.isEmpty()) {
        setLastError(tr("Не удалось открыть смену"));
        return false;
    }
    setLastError(QString{});
    refresh();
    emit shiftOpened();
    return true;
}

bool ShiftViewModel::closeMyShift(const QString& closeTimeStr)
{
    if (m_myOpenShift.isEmpty()) {
        setLastError(tr("Нет открытой смены"));
        return false;
    }
    const QString shiftId = m_myOpenShift.value(QStringLiteral("id")).toString();
    return closeShiftForEmployee(shiftId, closeTimeStr);
}

bool ShiftViewModel::closeShiftForEmployee(const QString& shiftId, const QString& closeTimeStr)
{
    if (shiftId.isEmpty()) {
        setLastError(tr("Не указана смена"));
        return false;
    }
    const QDateTime dt = parseCloseTime(closeTimeStr);
    if (!dt.isValid()) {
        setLastError(tr("Неверный формат времени. Используйте HH:mm или dd.MM.yyyy HH:mm"));
        return false;
    }
    if (!application::ShiftService::closeShift(shiftId, dt.toUTC())) {
        setLastError(tr("Не удалось закрыть смену"));
        return false;
    }
    setLastError(QString{});
    refresh();
    emit shiftClosed();
    return true;
}

void ShiftViewModel::setLastError(const QString& message)
{
    if (m_lastError != message) {
        m_lastError = message;
        emit lastErrorChanged();
    }
}

QDateTime ShiftViewModel::parseCloseTime(const QString& closeTimeStr) const
{
    QString s = closeTimeStr.trimmed();
    if (s.isEmpty()) return QDateTime::currentDateTime();
    return parseCloseTimeNonNull(s);
}

QDateTime ShiftViewModel::parseCloseTimeNonNull(const QString& s) const
{
    QDate today = QDate::currentDate();

    // Try "HH:mm" or "H:mm"
    QTime t = QTime::fromString(s, "HH:mm");
    if (!t.isValid())
        t = QTime::fromString(s, "H:mm");
    if (t.isValid())
        return QDateTime(today, t, Qt::LocalTime);

    // Try "dd.MM.yyyy HH:mm"
    QDateTime dt = QDateTime::fromString(s, "dd.MM.yyyy HH:mm");
    if (dt.isValid()) return dt.toLocalTime();

    // Try "dd.MM.yyyy"
    QDate d = QDate::fromString(s, "dd.MM.yyyy");
    if (d.isValid())
        return QDateTime(d, QTime(23, 59, 59), Qt::LocalTime);

    return QDateTime();
}
