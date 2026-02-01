#include "AppStateViewModel.h"

AppStateViewModel::AppStateViewModel(QObject *parent)
    : QObject(parent)
    , m_currentRole(Waiter)
    , m_isAuthenticated(false)
{
}

void AppStateViewModel::loginAs(int role)
{
    if (m_currentRole != role || !m_isAuthenticated) {
        m_currentRole = role;
        m_isAuthenticated = true;
        emit currentRoleChanged();
        emit isAuthenticatedChanged();
    }
}

void AppStateViewModel::logout()
{
    if (m_isAuthenticated) {
        m_isAuthenticated = false;
        m_currentRole = Waiter;
        emit isAuthenticatedChanged();
        emit currentRoleChanged();
    }
}
