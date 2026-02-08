#pragma once

#include <QString>
#include <QSqlDatabase>

namespace application {

class Database {
public:
    static bool initialize(const QString& path = QStringLiteral("profitagent.db"));
    static QSqlDatabase connection();
};

} // namespace application
