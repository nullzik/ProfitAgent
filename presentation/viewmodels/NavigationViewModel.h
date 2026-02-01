#ifndef NAVIGATIONVIEWMODEL_H
#define NAVIGATIONVIEWMODEL_H

#include <QObject>
#include <QString>

class NavigationViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName CONSTANT)
    Q_PROPERTY(QString userRole READ userRole CONSTANT)
    Q_PROPERTY(QString avatarUrl READ avatarUrl CONSTANT)
    Q_PROPERTY(int activeMenuItem READ activeMenuItem NOTIFY activeMenuItemChanged)
    Q_PROPERTY(int currentSection READ currentSection NOTIFY currentSectionChanged)

public:
    enum Section {
        Dashboard = 0,
        Warehouse = 1,
        Menu = 2,
        Employees = 3,
        Finance = 4,
        Help = 5
    };
    Q_ENUM(Section)

    explicit NavigationViewModel(QObject *parent = nullptr);

    QString userName() const { return m_userName; }
    QString userRole() const { return m_userRole; }
    QString avatarUrl() const { return m_avatarUrl; }
    int activeMenuItem() const { return m_activeMenuItem; }
    int currentSection() const { return m_currentSection; }

    Q_INVOKABLE void setActiveMenuItem(int index);
    Q_INVOKABLE void setCurrentSection(int section);

signals:
    void activeMenuItemChanged(int index);
    void currentSectionChanged();

private:
    QString m_userName;
    QString m_userRole;
    QString m_avatarUrl;
    int m_activeMenuItem;
    int m_currentSection;
};

#endif // NAVIGATIONVIEWMODEL_H
