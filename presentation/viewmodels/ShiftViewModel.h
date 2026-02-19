#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

class ShiftViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasOpenShift READ hasOpenShift NOTIFY hasOpenShiftChanged)
    Q_PROPERTY(QVariantMap myOpenShift READ myOpenShift NOTIFY myOpenShiftChanged)
    Q_PROPERTY(QVariantList openShifts READ openShifts NOTIFY openShiftsChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit ShiftViewModel(QObject *parent = nullptr);

    bool hasOpenShift() const { return m_hasOpenShift; }
    QVariantMap myOpenShift() const { return m_myOpenShift; }
    QVariantList openShifts() const { return m_openShifts; }
    QString lastError() const { return m_lastError; }

    Q_INVOKABLE void setCurrentEmployeeId(const QString& id);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE bool openShift();
    Q_INVOKABLE bool closeMyShift(const QString& closeTimeStr);  // "HH:mm" or "dd.MM.yyyy HH:mm"
    Q_INVOKABLE bool closeShiftForEmployee(const QString& shiftId, const QString& closeTimeStr);

signals:
    void hasOpenShiftChanged();
    void myOpenShiftChanged();
    void openShiftsChanged();
    void lastErrorChanged();
    void shiftOpened();
    void shiftClosed();

private:
    void setLastError(const QString& message);
    QDateTime parseCloseTime(const QString& closeTimeStr) const;
    QDateTime parseCloseTimeNonNull(const QString& s) const;

    QString m_currentEmployeeId;
    bool m_hasOpenShift{false};
    QVariantMap m_myOpenShift;
    QVariantList m_openShifts;
    QString m_lastError;
};
