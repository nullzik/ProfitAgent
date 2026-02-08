#include "application/services/AuthService.h"
#include "application/database/Database.h"

#include <QSqlQuery>
#include <QCryptographicHash>

namespace application {

int AuthService::validate(const QString& login, const QString& password)
{
    if (login.isEmpty() || password.isEmpty())
        return -1;

    const QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    const QString hashStr = QString::fromUtf8(hash);

    QSqlQuery q(Database::connection());
    q.prepare(QStringLiteral(
        "SELECT role FROM users WHERE login = :login AND password_hash = :hash"));
    q.bindValue(QStringLiteral(":login"), login.trimmed());
    q.bindValue(QStringLiteral(":hash"), hashStr);

    if (!q.exec() || !q.next())
        return -1;

    return q.value(0).toInt();
}

} // namespace application
