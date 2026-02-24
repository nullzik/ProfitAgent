#include "WarehouseViewModel.h"

#include <QVariantMap>
#include <QDebug>

#include <cmath>
#include <cstdint>
#include <exception>

#include "domain/warehouse/IWarehouseService.h"
#include "domain/warehouse/Product.h"
#include "domain/value_objects/Quantity.h"
#include "domain/value_objects/Money.h"
#include "application/services/FinanceService.h"

using namespace domain;

WarehouseViewModel::WarehouseViewModel(IWarehouseService &service, QObject *parent)
    : QObject(parent)
    , m_service(service)
{
    reloadProducts();
}

void WarehouseViewModel::createProduct(const QString &productId,
                                       const QString &name,
                                       const QString &unit)
{
    try {
        const std::string id = productId.toStdString();
        const std::string nameStr = name.toStdString();

        Unit unitEnum = Unit::Kilogram;
        if (unit == "кг" || unit == "Кг" || unit == "Килограмм" || unit == "Kilogram") {
            unitEnum = Unit::Kilogram;
        } else if (unit == "Gram" || unit == "gram" || unit == "г" || unit == "Грамм") {
            unitEnum = Unit::Gram;
        } else if (unit == "Liter" || unit == "liter" || unit == "л" || unit == "Литр") {
            unitEnum = Unit::Liter;
        } else {
            unitEnum = Unit::Kilogram;
        }

        m_service.createProduct(id, nameStr, unitEnum);

        reloadProducts();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "WarehouseViewModel::createProduct failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while creating product");
        qWarning() << "WarehouseViewModel::createProduct failed with unknown exception";
        setLastError(msg);
    }
}

void WarehouseViewModel::deleteProduct(const QString &productId)
{
    try {
        const std::string id = productId.toStdString();
        m_service.deleteProduct(id);

        reloadProducts();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "WarehouseViewModel::deleteProduct failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while deleting product");
        qWarning() << "WarehouseViewModel::deleteProduct failed with unknown exception";
        setLastError(msg);
    }
}

void WarehouseViewModel::addProductBatch(const QString &productId,
                                         double quantity,
                                         double purchasePrice)
{
    try {
        const std::string id = productId.toStdString();
        Quantity qty{quantity};

        const auto minorUnits = static_cast<std::int64_t>(std::llround(purchasePrice * 100.0));
        Money price{minorUnits, "RUB"};

        m_service.addProductBatch(id, qty, price);

        // Финансовый учёт поставки: расход = количество * закупочная цена
        const double totalCostRubles = quantity * purchasePrice;
        if (totalCostRubles > 0.0) {
            // Найдём читаемое имя продукта, если оно есть в кэше
            QString productName = productId;
            for (const auto &v : m_products) {
                const auto map = v.toMap();
                if (map.value(QStringLiteral("id")).toString() == productId) {
                    productName = map.value(QStringLiteral("name")).toString();
                    break;
                }
            }
            const QString category = QStringLiteral("Поставка: %1").arg(productName);
            const QString description = QStringLiteral("%1 ед. по %2 ₽")
                .arg(QString::number(quantity, 'f', 2))
                .arg(QString::number(purchasePrice, 'f', 2));
            application::FinanceService::addTransaction(
                application::FinanceService::Expense,
                totalCostRubles,
                category,
                description);
        }

        reloadProducts();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "WarehouseViewModel::addProductBatch failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while adding product batch");
        qWarning() << "WarehouseViewModel::addProductBatch failed with unknown exception";
        setLastError(msg);
    }
}

void WarehouseViewModel::writeOffProduct(const QString &productId, double quantity)
{
    try {
        const std::string id = productId.toStdString();
        Quantity qty{quantity};

        (void)m_service.writeOffProduct(id, qty);

        reloadProducts();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "WarehouseViewModel::writeOffProduct failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while writing off product");
        qWarning() << "WarehouseViewModel::writeOffProduct failed with unknown exception";
        setLastError(msg);
    }
}

void WarehouseViewModel::setStopList(const QString &productId, bool enabled)
{
    try {
        const std::string id = productId.toStdString();
        m_service.setStopList(id, enabled);

        reloadProducts();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "WarehouseViewModel::setStopList failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while changing stop-list state");
        qWarning() << "WarehouseViewModel::setStopList failed with unknown exception";
        setLastError(msg);
    }
}

void WarehouseViewModel::reloadProducts()
{
    m_products.clear();

    const auto allProducts = m_service.getAllProducts();

    for (const auto &product : allProducts) {
        QVariantMap item;
        item.insert(QStringLiteral("id"), QString::fromStdString(product.id()));
        item.insert(QStringLiteral("name"), QString::fromStdString(product.name()));

        const auto availableQty = m_service.getAvailableQuantity(product.id());
        item.insert(QStringLiteral("availableQuantity"), availableQty.value());

        QString unitStr;
        switch (product.unit()) {
            case Unit::Kilogram:
                unitStr = QStringLiteral("Kilogram");
                break;
            case Unit::Gram:
                unitStr = QStringLiteral("Gram");
                break;
            case Unit::Liter:
                unitStr = QStringLiteral("Liter");
                break;
        }
        item.insert(QStringLiteral("unit"), unitStr);

        item.insert(QStringLiteral("isInStopList"), product.isInStopList());

        m_products.append(item);
    }

    emit productsChanged();
}

void WarehouseViewModel::setLastError(const QString &message)
{
    if (m_lastError == message)
        return;

    m_lastError = message;
    emit lastErrorChanged();
}
