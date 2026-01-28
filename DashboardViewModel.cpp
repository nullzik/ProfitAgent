#include "DashboardViewModel.h"
#include <QDebug>

OperationsModel::OperationsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // Тестовые данные
    m_operations.append(OperationItem("Продажа товара А", "Продажа", "Иван Иванов", "15.01.2024"));
    m_operations.append(OperationItem("Закупка материалов", "Закупка", "Петр Петров", "14.01.2024"));
    m_operations.append(OperationItem("Продажа товара Б", "Продажа", "Мария Сидорова", "13.01.2024"));
    m_operations.append(OperationItem("Оплата аренды", "Расход", "ООО Аренда", "12.01.2024"));
    m_operations.append(OperationItem("Продажа товара В", "Продажа", "Алексей Козлов", "11.01.2024"));
    m_operations.append(OperationItem("Закупка товара", "Закупка", "ООО Поставщик", "10.01.2024"));
    m_operations.append(OperationItem("Продажа товара Г", "Продажа", "Елена Смирнова", "09.01.2024"));
    m_operations.append(OperationItem("Оплата услуг", "Расход", "ООО Услуги", "08.01.2024"));
}

int OperationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_operations.size();
}

QVariant OperationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_operations.size())
        return QVariant();

    const OperationItem &item = m_operations.at(index.row());

    switch (role) {
    case NameRole:
        return item.name();
    case TypeRole:
        return item.type();
    case SenderRole:
        return item.sender();
    case DateRole:
        return item.date();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> OperationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TypeRole] = "type";
    roles[SenderRole] = "sender";
    roles[DateRole] = "date";
    return roles;
}

DashboardViewModel::DashboardViewModel(QObject *parent)
    : QObject(parent)
    , m_userName("Иван")
    , m_revenue("1 250 000 ₽")
    , m_revenueChange("+12.5%")
    , m_netProfit("850 000 ₽")
    , m_netProfitChange("+8.3%")
    , m_salesCount("156")
    , m_salesCountChange("+5.2%")
    , m_operationsModel(new OperationsModel(this))
    , m_currentPage(1)
    , m_totalPages(3)
{
}

void DashboardViewModel::setCurrentPage(int page)
{
    if (page >= 1 && page <= m_totalPages && page != m_currentPage) {
        m_currentPage = page;
        emit currentPageChanged();
    }
}

