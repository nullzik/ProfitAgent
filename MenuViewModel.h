#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>

namespace domain {
class IMenuService;
class IWarehouseService;
}

// ViewModel для экрана меню.
// Отвечает только за адаптацию доменного сервиса к удобному для QML виду.
class MenuViewModel : public QObject
{
    Q_OBJECT

    // Список блюд для UI.
    // Каждый элемент — QVariantMap с ключами:
    //  - "id"               : QString
    //  - "name"             : QString
    //  - "salePrice"        : double (в рублях)
    //  - "costPrice"        : double (себестоимость в рублях)
    //  - "isAvailable"      : bool
    Q_PROPERTY(QVariantList dishes READ dishes NOTIFY dishesChanged)

    // Текст последней ошибки доменного слоя / валидации.
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit MenuViewModel(domain::IMenuService &menuService,
                          domain::IWarehouseService &warehouseService,
                          QObject *parent = nullptr);

    QVariantList dishes() const { return m_dishes; }
    QString lastError() const { return m_lastError; }

    // Методы для вызова из QML.
    Q_INVOKABLE void createDish(const QString &dishId,
                               const QString &name,
                               double salePrice);
    Q_INVOKABLE void updateDish(const QString &dishId,
                                const QString &name,
                                double salePrice,
                                bool isAvailable);
    Q_INVOKABLE void deleteDish(const QString &dishId);
    Q_INVOKABLE QVariantList getRecipe(const QString &dishId);
    Q_INVOKABLE void setRecipe(const QString &dishId,
                               const QVariantList &ingredients);

signals:
    void dishesChanged();
    void lastErrorChanged();

private:
    void reloadDishes();
    void setLastError(const QString &message);

    domain::IMenuService &m_menuService;
    domain::IWarehouseService &m_warehouseService;
    QVariantList m_dishes;
    QString m_lastError;
};

