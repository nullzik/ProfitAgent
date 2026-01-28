#include "NavigationViewModel.h"

NavigationViewModel::NavigationViewModel(QObject *parent)
    : QObject(parent)
    , m_userName("Иван Иванов")
    , m_userRole("Администратор")
    , m_avatarUrl("")
    , m_activeMenuItem(0) // Главная страница активна по умолчанию
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



