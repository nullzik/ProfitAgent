#include "ChefViewModel.h"
#include <QDebug>

ChefViewModel::ChefViewModel(QObject *parent)
    : QObject(parent)
    , m_selectedProductId(-1)
    , m_isProductDialogOpen(false)
{
}

void ChefViewModel::onProductSelected(int productId)
{
    if (m_selectedProductId != productId) {
        m_selectedProductId = productId;
        emit selectedProductIdChanged();
    }
    openProductOperation(productId);
}

void ChefViewModel::openProductOperation(int productId)
{
    m_selectedProductId = productId;
    m_isProductDialogOpen = true;
    emit selectedProductIdChanged();
    emit isProductDialogOpenChanged();
}

void ChefViewModel::addProduct()
{
    qDebug() << "Add product" << m_selectedProductId;
}

void ChefViewModel::writeOffProduct()
{
    qDebug() << "Write off product" << m_selectedProductId;
}

void ChefViewModel::closeProductDialog()
{
    m_isProductDialogOpen = false;
    emit isProductDialogOpenChanged();
}
