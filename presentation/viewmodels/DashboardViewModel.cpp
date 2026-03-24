#include "DashboardViewModel.h"

#include "application/services/FinanceService.h"
#include "application/services/ActivityService.h"

#include <QLocale>
#include <QDebug>
#include <algorithm>
#include <cmath>

OperationsModel::OperationsModel(QObject *parent)
    : QAbstractListModel(parent)
{
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
    case DetailsRole:
        return item.details();
    case AmountRole:
        return item.amount();
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
    roles[DetailsRole] = "details";
    roles[AmountRole] = "amount";
    return roles;
}

void OperationsModel::setOperations(QList<OperationItem> operations)
{
    beginResetModel();
    m_operations = std::move(operations);
    endResetModel();
}

static QString formatPercentChange(double current, double previous)
{
    if (std::abs(previous) < 1e-9) {
        // Если за предыдущий период не было данных, не показываем искусственно "+100%".
        // Для нулевых значений показываем "0%", иначе — пустую строку (карточка спрячет индикатор изменения).
        if (std::abs(current) < 1e-9)
            return QStringLiteral("0%");
        return QString();
    }
    const double pct = (current - previous) / std::abs(previous) * 100.0;
    const QString sign = (pct >= 0.0) ? QStringLiteral("+") : QString();
    return sign + QString::number(pct, 'f', 1) + QStringLiteral("%");
}

DashboardViewModel::DashboardViewModel(QObject *parent)
    : QObject(parent)
    , m_userName(QString())
    , m_revenue(QStringLiteral("0 ₽"))
    , m_revenueChange(QStringLiteral("0%"))
    , m_netProfit(QStringLiteral("0 ₽"))
    , m_netProfitChange(QStringLiteral("0%"))
    , m_salesCount(QStringLiteral("0"))
    , m_salesCountChange(QStringLiteral("0%"))
    , m_operationsModel(new OperationsModel(this))
    , m_currentPage(1)
    , m_totalPages(1)
{
    reload();
}

namespace {

QString eventTypeFilterForIndex(int index)
{
    switch (index) {
    case 1: return QStringLiteral("Продажа");
    case 2: return QStringLiteral("Поставка");
    case 3: return QStringLiteral("Списание");
    case 4: return QStringLiteral("Премия");
    case 5: return QStringLiteral("Штраф");
    case 6: return QStringLiteral("Зарплата");
    case 7: return QStringLiteral("Доход");
    case 8: return QStringLiteral("Расход");
    case 9: return QStringLiteral("Блюдо");
    case 10: return QStringLiteral("Склад");
    case 11: return QStringLiteral("Сотрудники");
    default:
        return QString();
    }
}

static bool isPositiveAmountType(const QString& eventType)
{
    if (eventType == QStringLiteral("Продажа")) return true;
    if (eventType == QStringLiteral("Доход")) return true;
    if (eventType == QStringLiteral("Штраф")) return true;
    // Everything else is treated as expense/negative if it has an amount.
    return false;
}

} // namespace

void DashboardViewModel::setCurrentPage(int page)
{
    if (page < 1) page = 1;
    if (page > m_totalPages) page = m_totalPages;
    if (page == m_currentPage) return;
    m_currentPage = page;
    emit currentPageChanged();
    reloadOperations();
}

void DashboardViewModel::setUserName(const QString& name)
{
    if (m_userName != name) {
        m_userName = name;
        emit userNameChanged();
    }
}

void DashboardViewModel::reload()
{
    reloadKpis();
    updatePagination();
    reloadOperations();
}

void DashboardViewModel::setFilterIndex(int index)
{
    if (index < 0) index = 0;
    if (index == m_filterIndex) return;
    m_filterIndex = index;
    emit filterIndexChanged();
    m_currentPage = 1;
    emit currentPageChanged();
    updatePagination();
    reloadOperations();
}

void DashboardViewModel::logUiEvent(const QString& eventType,
                                    const QString& title,
                                    const QString& details,
                                    double amountRubles)
{
    const qint64 minor = static_cast<qint64>(std::llround(amountRubles * 100.0));
    const bool hasAmount = std::abs(minor) > 0;
    const QString sender = m_userName.isEmpty()
        ? QStringLiteral("Пользователь")
        : m_userName;

    application::ActivityService::logEvent(
        eventType.trimmed(),
        title.trimmed(),
        sender,
        details.trimmed(),
        QString(),               // source
        QString(),               // sourceId
        -1,                      // createdAtMs -> now
        minor,
        hasAmount);

    reload();
}

void DashboardViewModel::reloadKpis()
{
    const int days = 30;

    const double revenueNow = application::FinanceService::getSalesRevenueForDays(days, 0);
    const double revenuePrev = application::FinanceService::getSalesRevenueForDays(days, days);
    const double profitNow = application::FinanceService::getNetProfitForDays(days, 0);
    const double profitPrev = application::FinanceService::getNetProfitForDays(days, days);
    const int salesNow = application::FinanceService::getSalesCountForDays(days, 0);
    const int salesPrev = application::FinanceService::getSalesCountForDays(days, days);

    const QLocale ru(QLocale::Russian);

    const QString newRevenue = ru.toCurrencyString(revenueNow, QStringLiteral("₽"));
    const QString newRevenueChange = formatPercentChange(revenueNow, revenuePrev);
    const QString newProfit = ru.toCurrencyString(profitNow, QStringLiteral("₽"));
    const QString newProfitChange = formatPercentChange(profitNow, profitPrev);
    const QString newSales = QString::number(salesNow);
    const QString newSalesChange = formatPercentChange(static_cast<double>(salesNow), static_cast<double>(salesPrev));

    if (m_revenue != newRevenue) { m_revenue = newRevenue; emit revenueChanged(); }
    if (m_revenueChange != newRevenueChange) { m_revenueChange = newRevenueChange; emit revenueChangeChanged(); }
    if (m_netProfit != newProfit) { m_netProfit = newProfit; emit netProfitChanged(); }
    if (m_netProfitChange != newProfitChange) { m_netProfitChange = newProfitChange; emit netProfitChangeChanged(); }
    if (m_salesCount != newSales) { m_salesCount = newSales; emit salesCountChanged(); }
    if (m_salesCountChange != newSalesChange) { m_salesCountChange = newSalesChange; emit salesCountChangeChanged(); }
}

void DashboardViewModel::updatePagination()
{
    const QString typeFilter = eventTypeFilterForIndex(m_filterIndex);
    m_totalOperations = application::ActivityService::getTotalCount(typeFilter);
    const int pages = std::max(1, (m_totalOperations + m_pageSize - 1) / m_pageSize);
    if (m_totalPages != pages) {
        m_totalPages = pages;
        emit totalPagesChanged();
    }
    if (m_currentPage > m_totalPages) {
        m_currentPage = m_totalPages;
        emit currentPageChanged();
    }
}

void DashboardViewModel::reloadOperations()
{
    const int offset = (m_currentPage - 1) * m_pageSize;
    const QString typeFilter = eventTypeFilterForIndex(m_filterIndex);
    const QVariantList events = application::ActivityService::getRecentEvents(m_pageSize, offset, typeFilter);

    QList<OperationItem> ops;
    ops.reserve(events.size());

    for (const auto& v : events) {
        const QVariantMap m = v.toMap();
        const QString title = m.value(QStringLiteral("title")).toString();
        const QString details = m.value(QStringLiteral("details")).toString();
        const QString eventType = m.value(QStringLiteral("eventType")).toString();
        const QString name = title;

        QString amountText;
        const bool hasAmount = m.value(QStringLiteral("hasAmount")).toBool();
        if (hasAmount) {
            const double amount = m.value(QStringLiteral("amountRubles")).toDouble();
            const bool positive = isPositiveAmountType(eventType);
            const double absAmount = std::abs(amount);
            const QLocale ru(QLocale::Russian);
            const QString money = ru.toCurrencyString(absAmount, QStringLiteral("₽"));
            amountText = QStringLiteral("%1%2").arg(positive ? "+" : "-").arg(money);
        }

        ops.append(OperationItem(
            name,
            eventType,
            m.value(QStringLiteral("sender")).toString(),
            m.value(QStringLiteral("createdAtFormatted")).toString(),
            details,
            amountText
        ));
    }

    m_operationsModel->setOperations(std::move(ops));
}
