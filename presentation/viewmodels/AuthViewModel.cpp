#include "AuthViewModel.h"
#include "application/services/AuthService.h"
#include <QDebug>

AuthViewModel::AuthViewModel(QObject *parent)
    : QObject(parent)
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

void AuthViewModel::performLogin()
{
    const int role = application::AuthService::validate(m_login, m_password);
    if (role >= 0) {
        m_isAuthenticated = true;
        emit isAuthenticatedChanged();
        emit loginSuccess(role, m_login);
    } else {
        emit loginFailed();
    }
}

void AuthViewModel::logout()
{
    m_isAuthenticated = false;
    m_login = "";
    m_password = "";
    emit isAuthenticatedChanged();
}
