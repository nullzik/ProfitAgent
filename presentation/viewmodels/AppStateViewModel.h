#ifndef APPSTATEVIEWMODEL_H
#define APPSTATEVIEWMODEL_H

#include <QObject>

class AppStateViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentRole READ currentRole NOTIFY currentRoleChanged)
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)
    Q_PROPERTY(QString currentUserName READ currentUserName NOTIFY currentUserNameChanged)

public:
    enum Role {
        Waiter = 0,
        Chef = 1,
        Manager = 2
    };
    Q_ENUM(Role)

    explicit AppStateViewModel(QObject *parent = nullptr);

    int currentRole() const { return m_currentRole; }
    bool isAuthenticated() const { return m_isAuthenticated; }
    QString currentUserName() const { return m_currentUserName; }

    Q_INVOKABLE void loginAs(int role);
    Q_INVOKABLE void setCurrentUser(const QString& login, int role);
    Q_INVOKABLE void logout();

signals:
    void currentRoleChanged();
    void isAuthenticatedChanged();
    void currentUserNameChanged();

private:
    int m_currentRole;
    bool m_isAuthenticated;
    QString m_currentUserName;
};

#endif // APPSTATEVIEWMODEL_H
