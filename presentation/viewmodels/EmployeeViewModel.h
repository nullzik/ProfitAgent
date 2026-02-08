#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QString>

class EmployeeViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList employees READ employees NOTIFY employeesChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit EmployeeViewModel(QObject *parent = nullptr);

    QVariantList employees() const { return m_employees; }
    QString lastError() const { return m_lastError; }

    Q_INVOKABLE void reloadEmployees();
    Q_INVOKABLE QVariantMap getEmployeeById(const QString& id) const;
    Q_INVOKABLE bool createEmployee(const QString& fullName, int age, const QString& phone,
                                    const QString& address, int role, double hourlyRate,
                                    const QString& login = QString(), const QString& password = QString());
    Q_INVOKABLE bool updateEmployee(const QString& id, const QString& fullName, int age, const QString& phone,
                                    const QString& address, int role, double hourlyRate,
                                    const QString& login = QString(), const QString& password = QString());

signals:
    void employeesChanged();
    void lastErrorChanged();

private:
    void setLastError(const QString& message);

    QVariantList m_employees;
    QString m_lastError;
};
