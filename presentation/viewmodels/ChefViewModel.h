#ifndef CHEFVIEWMODEL_H
#define CHEFVIEWMODEL_H

#include <QObject>
#include <QString>

class ChefViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectedProductId READ selectedProductId NOTIFY selectedProductIdChanged)
    Q_PROPERTY(bool isProductDialogOpen READ isProductDialogOpen NOTIFY isProductDialogOpenChanged)

public:
    explicit ChefViewModel(QObject *parent = nullptr);

    int selectedProductId() const { return m_selectedProductId; }
    bool isProductDialogOpen() const { return m_isProductDialogOpen; }

    Q_INVOKABLE void onProductSelected(int productId);
    Q_INVOKABLE void openProductOperation(int productId);
    Q_INVOKABLE void addProduct();
    Q_INVOKABLE void writeOffProduct();
    Q_INVOKABLE void closeProductDialog();

signals:
    void selectedProductIdChanged();
    void isProductDialogOpenChanged();

private:
    int m_selectedProductId;
    bool m_isProductDialogOpen;
};

#endif // CHEFVIEWMODEL_H
