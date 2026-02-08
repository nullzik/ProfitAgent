#include "NavigationViewModel.h"

NavigationViewModel::NavigationViewModel(QObject *parent)
    : QObject(parent)
    , m_userName("")
    , m_userRole("")
    , m_avatarUrl("")
    , m_activeMenuItem(0)
    , m_currentSection(Dashboard)
{
}

void NavigationViewModel::setActiveMenuItem(int index)
{
    if (index != m_activeMenuItem) {
        m_activeMenuItem = index;
        emit activeMenuItemChanged(index);
        setCurrentSection(index);
    }
}

void NavigationViewModel::setCurrentSection(int section)
{
    if (m_currentSection != section) {
        m_currentSection = section;
        emit currentSectionChanged();
    }
}

void NavigationViewModel::setCurrentUser(const QString& login, int role)
{
    const QString roleNames[] = {
        QStringLiteral("Официант"), QStringLiteral("Повар"), QStringLiteral("Менеджер")
    };
    const QString newRole = role >= 0 && role < 3 ? roleNames[role] : QStringLiteral("Пользователь");

    if (m_userName != login || m_userRole != newRole) {
        m_userName = login;
        m_userRole = newRole;
        emit userNameChanged();
        emit userRoleChanged();
    }
}
