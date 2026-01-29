#include "AuthViewModel.h"
#include <QDebug>

AuthViewModel::AuthViewModel(QObject *parent)
    : QObject(parent)
    , m_login("")
    , m_password("")
    , m_selectedRole(Waiter)
    , m_isAuthenticated(false)
{
}

void AuthViewModel::setLogin(const QString &login)
{
    if (m_login != login) {
        m_login = login;
        emit loginChanged();
    }
}

void AuthViewModel::setPassword(const QString &password)
{
    if (m_password != password) {
        m_password = password;
        emit passwordChanged();
    }
}

void AuthViewModel::setSelectedRole(int role)
{
    if (m_selectedRole != role) {
        m_selectedRole = role;
        emit selectedRoleChanged();
    }
}

void AuthViewModel::performLogin()
{
    // Заглушка: всегда успешный вход
    // Никаких проверок пароля
    m_isAuthenticated = true;
    emit isAuthenticatedChanged();
    emit loginSuccess(m_selectedRole);
}

void AuthViewModel::logout()
{
    m_isAuthenticated = false;
    m_login = "";
    m_password = "";
    emit isAuthenticatedChanged();
}









