#ifndef WAITERVIEWMODEL_H
#define WAITERVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QVariantList>

namespace application {
class OrderService;
}
class WarehouseViewModel;

class WaiterViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectedTableId READ selectedTableId NOTIFY selectedTableIdChanged)
    Q_PROPERTY(bool isOrderDialogOpen READ isOrderDialogOpen NOTIFY isOrderDialogOpenChanged)
    Q_PROPERTY(QString orderMessage READ orderMessage NOTIFY orderMessageChanged)
    Q_PROPERTY(QVariantList tables READ tables NOTIFY tablesChanged)

public:
    explicit WaiterViewModel(QObject *parent = nullptr);

    void setOrderService(application::OrderService* orderService);
    void setWarehouseViewModel(WarehouseViewModel* warehouseViewModel);

    int selectedTableId() const { return m_selectedTableId; }
    bool isOrderDialogOpen() const { return m_isOrderDialogOpen; }
    QString orderMessage() const { return m_orderMessage; }
    QVariantList tables() const { return m_tables; }

    Q_INVOKABLE void onTableSelected(int tableId);
    Q_INVOKABLE void openOrderEntry(int tableId);
    Q_INVOKABLE void closeOrderEntry();
    Q_INVOKABLE bool placeOrder(const QVariantList& orderItems);

signals:
    void selectedTableIdChanged();
    void isOrderDialogOpenChanged();
    void orderMessageChanged();
    void orderPlacedSuccess();
    void orderPlacedFailed(const QString& reason);
    void tablesChanged();

private:
    void setOrderMessage(const QString& message);
    void clearOrderMessage();
    void refreshTables();

    application::OrderService* m_orderService = nullptr;
    WarehouseViewModel* m_warehouseViewModel = nullptr;
    int m_selectedTableId;
    bool m_isOrderDialogOpen;
    QString m_orderMessage;
    QVariantList m_tables;
};

#endif // WAITERVIEWMODEL_H
