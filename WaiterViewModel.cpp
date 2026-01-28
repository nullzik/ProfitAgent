#include "WaiterViewModel.h"

WaiterViewModel::WaiterViewModel(QObject *parent)
    : QObject(parent)
    , m_selectedTableId(-1)
    , m_isOrderDialogOpen(false)
{
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





