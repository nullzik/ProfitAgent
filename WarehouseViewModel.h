#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>

namespace domain {
class IWarehouseService;
}

// ViewModel для экрана склада.
// Отвечает только за адаптацию доменного сервиса к удобному для QML виду.
class WarehouseViewModel : public QObject
{
    Q_OBJECT

    // Список продуктов для UI.
    // Каждый элемент — QVariantMap с ключами:
    //  - "id"               : QString
    //  - "name"             : QString
    //  - "availableQuantity": double
    //  - "unit"             : QString ("Kilogram", "Gram", "Liter")
    //  - "isInStopList"     : bool
    Q_PROPERTY(QVariantList products READ products NOTIFY productsChanged)

    // Текст последней ошибки доменного слоя / валидации.
    // Пустая строка означает отсутствие ошибки.
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit WarehouseViewModel(domain::IWarehouseService &service,
                                QObject *parent = nullptr);

    QVariantList products() const { return m_products; }

    // Последняя ошибка для отображения в QML.
    QString lastError() const { return m_lastError; }

    // Методы для вызова из QML. Здесь нет бизнес‑логики — только делегирование
    // в доменный сервис и обновление snapshot для UI.
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

signals:
    void productsChanged();
    void lastErrorChanged();

private:
    void reloadProducts();
    void setLastError(const QString &message);

    domain::IWarehouseService &m_service;
    QVariantList m_products;
    QString m_lastError;
};


