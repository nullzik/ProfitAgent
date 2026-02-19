#pragma once

#include <QString>

namespace application {

struct AuthResult {
    int role{-1};           // 0=Waiter, 1=Chef, 2=Manager
    QString employeeId;     // empty if no employee linked
};

class AuthService {
public:
    // Validates credentials. Returns AuthResult with role -1 on failure.
    static AuthResult validate(const QString& login, const QString& password);
};

} // namespace application
