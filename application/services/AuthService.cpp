#include "application/services/AuthService.h"
#include "application/database/Database.h"

#include <QSqlQuery>
#include <QCryptographicHash>

namespace application {

AuthResult AuthService::validate(const QString& login, const QString& password)
{
    AuthResult result;
    if (login.isEmpty() || password.isEmpty())
        return result;

    const QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    const QString hashStr = QString::fromUtf8(hash);

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT role, employee_id FROM users WHERE login = :login AND password_hash = :hash"));
    q.bindValue(QStringLiteral(":login"), login.trimmed());
    q.bindValue(QStringLiteral(":hash"), hashStr);

    if (!q.exec() || !q.next())
        return result;

    result.role = q.value(0).toInt();
    result.employeeId = q.value(1).toString();
    return result;
}

} // namespace application
