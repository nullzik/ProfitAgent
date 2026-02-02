#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>

namespace domain {
class IWarehouseService;
}

class WarehouseViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList products READ products NOTIFY productsChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit WarehouseViewModel(domain::IWarehouseService &service,
                                QObject *parent = nullptr);

    QVariantList products() const { return m_products; }
    QString lastError() const { return m_lastError; }

    Q_INVOKABLE void createProduct(const QString &productId,
                                    const QString &name,
                                    const QString &unit);
    Q_INVOKABLE void deleteProduct(const QString &productId);
    Q_INVOKABLE void addProductBatch(const QString &productId,
                                     double quantity,
                                     double purchasePrice);
    Q_INVOKABLE void writeOffProduct(const QString &productId,
                                     double quantity);
    Q_INVOKABLE void setStopList(const QString &productId, bool enabled);
    Q_INVOKABLE void reloadProducts();

signals:
    void productsChanged();
    void lastErrorChanged();

private:
    void setLastError(const QString &message);

    domain::IWarehouseService &m_service;
    QVariantList m_products;
    QString m_lastError;
};
