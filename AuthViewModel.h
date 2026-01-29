#ifndef AUTHVIEWMODEL_H
#define AUTHVIEWMODEL_H

#include <QObject>
#include <QString>

class AuthViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(int selectedRole READ selectedRole WRITE setSelectedRole NOTIFY selectedRoleChanged)
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)

public:
    enum Role {
        Waiter = 0,
        Chef = 1,
        Manager = 2,
        Director = 3
    };
    Q_ENUM(Role)

    explicit AuthViewModel(QObject *parent = nullptr);

    QString login() const { return m_login; }
    void setLogin(const QString &login);

    QString password() const { return m_password; }
    void setPassword(const QString &password);

    int selectedRole() const { return m_selectedRole; }
    void setSelectedRole(int role);

    bool isAuthenticated() const { return m_isAuthenticated; }

    Q_INVOKABLE void performLogin();
    Q_INVOKABLE void logout();

signals:
    void loginChanged();
    void passwordChanged();
    void selectedRoleChanged();
    void isAuthenticatedChanged();
    void loginSuccess(int role);
    void loginFailed();

private:
    QString m_login;
    QString m_password;
    int m_selectedRole;
    bool m_isAuthenticated;
};

#endif // AUTHVIEWMODEL_H









