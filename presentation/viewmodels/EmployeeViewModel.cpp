#include "EmployeeViewModel.h"
#include "application/services/EmployeeService.h"

#include <QDebug>

EmployeeViewModel::EmployeeViewModel(QObject *parent)
    : QObject(parent)
{
    reloadEmployees();
}

void EmployeeViewModel::reloadEmployees()
{
    m_employees = application::EmployeeService::getAllEmployees();
    emit employeesChanged();
}

QVariantMap EmployeeViewModel::getEmployeeById(const QString& id) const
{
    return application::EmployeeService::getEmployeeById(id);
}

bool EmployeeViewModel::createEmployee(const QString& fullName, int age, const QString& phone,
                                       const QString& address, int role, double hourlyRate,
                                       const QString& login, const QString& password)
{
    try {
        const bool ok = application::EmployeeService::createEmployee(fullName, age, phone, address, role, hourlyRate, login, password);
        if (ok) {
            reloadEmployees();
            setLastError(QString{});
            return true;
        }
        setLastError(tr("Не удалось создать сотрудника"));
        return false;
    } catch (const std::exception& e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "EmployeeViewModel::createEmployee failed:" << msg;
        setLastError(msg);
        return false;
    } catch (...) {
        setLastError(tr("Неизвестная ошибка"));
        return false;
    }
}

bool EmployeeViewModel::updateEmployee(const QString& id, const QString& fullName, int age, const QString& phone,
                                       const QString& address, int role, double hourlyRate,
                                       const QString& login, const QString& password)
{
    try {
        const bool ok = application::EmployeeService::updateEmployee(id, fullName, age, phone, address, role, hourlyRate, login, password);
        if (ok) {
            reloadEmployees();
            setLastError(QString{});
            return true;
        }
        setLastError(tr("Не удалось обновить сотрудника"));
        return false;
    } catch (const std::exception& e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "EmployeeViewModel::updateEmployee failed:" << msg;
        setLastError(msg);
        return false;
    } catch (...) {
        setLastError(tr("Неизвестная ошибка"));
        return false;
    }
}

void EmployeeViewModel::setLastError(const QString& message)
{
    if (m_lastError != message) {
        m_lastError = message;
        emit lastErrorChanged();
    }
}
