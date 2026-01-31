#ifndef APPSTATEVIEWMODEL_H
#define APPSTATEVIEWMODEL_H

#include <QObject>

class AppStateViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentRole READ currentRole NOTIFY currentRoleChanged)
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY isAuthenticatedChanged)

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

    Q_INVOKABLE void loginAs(int role);
    Q_INVOKABLE void logout();

signals:
    void currentRoleChanged();
    void isAuthenticatedChanged();

private:
    int m_currentRole;
    bool m_isAuthenticated;
};

#endif // APPSTATEVIEWMODEL_H









