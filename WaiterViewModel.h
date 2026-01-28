#ifndef WAITERVIEWMODEL_H
#define WAITERVIEWMODEL_H

#include <QObject>
#include <QString>

class WaiterViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectedTableId READ selectedTableId NOTIFY selectedTableIdChanged)
    Q_PROPERTY(bool isOrderDialogOpen READ isOrderDialogOpen NOTIFY isOrderDialogOpenChanged)

public:
    explicit WaiterViewModel(QObject *parent = nullptr);

    int selectedTableId() const { return m_selectedTableId; }
    bool isOrderDialogOpen() const { return m_isOrderDialogOpen; }

    Q_INVOKABLE void onTableSelected(int tableId);
    Q_INVOKABLE void openOrderEntry(int tableId);
    Q_INVOKABLE void closeOrderEntry();

signals:
    void selectedTableIdChanged();
    void isOrderDialogOpenChanged();

private:
    int m_selectedTableId;
    bool m_isOrderDialogOpen;
};

#endif // WAITERVIEWMODEL_H





