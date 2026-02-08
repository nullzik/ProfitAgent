#pragma once

#include <QString>
#include <QVariantList>

namespace application {

class EmployeeService {
public:
    // Returns list of employees as QVariantList of maps (incl. login if has user)
    static QVariantList getAllEmployees();

    // Returns one employee by id, or empty map if not found
    static QVariantMap getEmployeeById(const QString& id);

    // Creates employee. If login non-empty, creates user for login (password hashed). role: 0=Waiter, 1=Chef, 2=Manager, 3=Director, 4=Cashier, 5=Other
    static bool createEmployee(const QString& fullName, int age, const QString& phone,
                               const QString& address, int role, double hourlyRate,
                               const QString& login = QString(), const QString& password = QString());

    // Updates employee. If password non-empty, updates user password. login empty = don't change user login.
    static bool updateEmployee(const QString& id, const QString& fullName, int age, const QString& phone,
                               const QString& address, int role, double hourlyRate,
                               const QString& login = QString(), const QString& password = QString());
};

} // namespace application
