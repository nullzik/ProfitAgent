#pragma once

#include <QString>

namespace application {

class AuthService {
public:
    // Validates credentials. Returns role (0=Waiter, 1=Chef, 2=Manager) or -1 on failure.
    static int validate(const QString& login, const QString& password);
};

} // namespace application
