#include "WaiterViewModel.h"

#include <QVariantMap>
#include <QDebug>

#include "application/services/OrderService.h"
#include "WarehouseViewModel.h"

WaiterViewModel::WaiterViewModel(QObject *parent)
    : QObject(parent)
    , m_selectedTableId(-1)
    , m_isOrderDialogOpen(false)
{
}

void WaiterViewModel::setOrderService(application::OrderService* orderService)
{
    m_orderService = orderService;
    refreshTables();
}

void WaiterViewModel::setWarehouseViewModel(WarehouseViewModel* warehouseViewModel)
{
    m_warehouseViewModel = warehouseViewModel;
}

void WaiterViewModel::onTableSelected(int tableId)
{
    if (m_selectedTableId != tableId) {
        m_selectedTableId = tableId;
        emit selectedTableIdChanged();
    }
    openOrderEntry(tableId);
}

void WaiterViewModel::openOrderEntry(int tableId)
{
    m_selectedTableId = tableId;
    m_isOrderDialogOpen = true;
    emit selectedTableIdChanged();
    emit isOrderDialogOpenChanged();
}

void WaiterViewModel::closeOrderEntry()
{
    m_isOrderDialogOpen = false;
    emit isOrderDialogOpenChanged();
}

bool WaiterViewModel::placeOrder(const QVariantList& orderItems)
{
    if (!m_orderService) {
        qWarning() << "WaiterViewModel::placeOrder: OrderService not set";
        emit orderPlacedFailed(tr("Сервис заказов не инициализирован"));
        return false;
    }

    if (orderItems.isEmpty()) {
        emit orderPlacedFailed(tr("Заказ пуст"));
        return false;
    }

    std::vector<std::pair<std::string, int>> dishes;
    dishes.reserve(orderItems.size());

    for (const auto& variant : orderItems) {
        const auto map = variant.toMap();
        const QString dishId = map.value(QStringLiteral("dishId")).toString();
        const int quantity = map.value(QStringLiteral("quantity")).toInt();

        if (dishId.isEmpty() || quantity <= 0)
            continue;

        dishes.emplace_back(dishId.toStdString(), quantity);
    }

    if (dishes.empty()) {
        emit orderPlacedFailed(tr("Заказ пуст"));
        return false;
    }

    const int tableId = m_selectedTableId >= 0 ? m_selectedTableId : 0;
    const bool ok = m_orderService->placeOrder(tableId, dishes);

    if (ok) {
        if (m_warehouseViewModel) {
            m_warehouseViewModel->reloadProducts();
        }
        refreshTables();
        setOrderMessage(tr("Заказ принят"));
        emit orderPlacedSuccess();
    } else {
        setOrderMessage(tr("Недостаточно ингредиентов"));
        emit orderPlacedFailed(tr("Недостаточно ингредиентов"));
    }

    return ok;
}

void WaiterViewModel::setOrderMessage(const QString& message)
{
    if (m_orderMessage != message) {
        m_orderMessage = message;
        emit orderMessageChanged();
    }
}

void WaiterViewModel::clearOrderMessage()
{
    setOrderMessage(QString{});
}

void WaiterViewModel::refreshTables()
{
    if (!m_orderService) return;

    m_tables.clear();
    constexpr int tableCount = 12;
    for (int i = 0; i < tableCount; ++i) {
        const auto summary = m_orderService->getTableSummary(i);

        QVariantList dishesList;
        for (const auto& d : summary.dishes) {
            QVariantMap dm;
            dm.insert(QStringLiteral("name"), QString::fromStdString(d.dishName));
            dm.insert(QStringLiteral("quantity"), d.quantity);
            dishesList.append(dm);
        }

        QVariantMap tableMap;
        tableMap.insert(QStringLiteral("tableIndex"), i);
        tableMap.insert(QStringLiteral("hasOrders"), summary.hasOrders);
        tableMap.insert(QStringLiteral("dishes"), dishesList);
        m_tables.append(tableMap);
    }

    emit tablesChanged();
}