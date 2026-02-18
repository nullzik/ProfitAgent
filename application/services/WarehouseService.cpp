#include "application/services/WarehouseService.h"

#include <chrono>
#include <stdexcept>
#include <utility>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include "domain/warehouse/StockBatch.h"

namespace domain {

namespace {

void ensurePositiveQuantity(const Quantity& q) {
    if (q.value() <= 0.0) {
        throw std::invalid_argument("quantity must be greater than zero");
    }
}

int unitToInt(Unit u) {
    switch (u) {
    case Unit::Kilogram: return 0;
    case Unit::Gram:     return 1;
    case Unit::Liter:    return 2;
    }
    return 0;
}

Unit intToUnit(int v) {
    switch (v) {
    case 0: return Unit::Kilogram;
    case 1: return Unit::Gram;
    case 2: return Unit::Liter;
    default: return Unit::Kilogram;
    }
}

void syncBatchesToDatabase(const Warehouse& warehouse)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        return;
    }

    QSqlQuery q(db);
    if (!q.exec(QStringLiteral("DELETE FROM warehouse_batches"))) {
        qWarning() << "Failed to clear warehouse_batches:" << q.lastError().text();
        return;
    }

    QSqlQuery insert(db);
    insert.prepare(QStringLiteral(
        "INSERT INTO warehouse_batches "
        "(product_id, quantity, purchase_price_minor_units, created_at) "
        "VALUES (:product_id, :quantity, :price, :created_at)"));

    for (const auto& batch : warehouse.batches()) {
        insert.bindValue(QStringLiteral(":product_id"), QString::fromStdString(batch.productId()));
        insert.bindValue(QStringLiteral(":quantity"), batch.quantity().value());
        insert.bindValue(QStringLiteral(":price"),
                         static_cast<qint64>(batch.purchasePrice().minorUnits()));

        const auto tp = batch.purchaseDate();
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            tp.time_since_epoch())
                            .count();
        insert.bindValue(QStringLiteral(":created_at"), static_cast<qint64>(ms));

        if (!insert.exec()) {
            qWarning() << "Failed to insert warehouse_batch:" << insert.lastError().text();
        }
    }
}

} // namespace

WarehouseService::WarehouseService(std::vector<Product> initialProducts)
{
    QSqlDatabase db = QSqlDatabase::database();

    bool loadedFromDb = false;
    if (db.isOpen()) {
        QSqlQuery q(db);
        if (q.exec(QStringLiteral(
                "SELECT id, name, unit, is_in_stop_list FROM warehouse_products"))) {
            while (q.next()) {
                const auto id = q.value(0).toString().toStdString();
                const auto name = q.value(1).toString().toStdString();
                const int unitInt = q.value(2).toInt();
                const bool isInStopList = q.value(3).toInt() != 0;

                Product p{id, name, intToUnit(unitInt), isInStopList};
                products_.emplace(id, std::move(p));
            }
            loadedFromDb = true;
        } else {
            qWarning() << "Failed to load warehouse_products:" << q.lastError().text();
        }

        // Load batches
        QSqlQuery qb(db);
        if (qb.exec(QStringLiteral(
                "SELECT product_id, quantity, purchase_price_minor_units, created_at "
                "FROM warehouse_batches "
                "ORDER BY created_at ASC, id ASC"))) {
            while (qb.next()) {
                const auto productId = qb.value(0).toString().toStdString();
                const double quantity = qb.value(1).toDouble();
                const auto priceMinor = static_cast<std::int64_t>(qb.value(2).toLongLong());
                const auto createdMs = qb.value(3).toLongLong();

                Quantity qty{quantity};
                Money price{priceMinor, "RUB"};
                const auto tp = std::chrono::system_clock::time_point{
                    std::chrono::milliseconds{createdMs}};

                StockBatch batch{productId, qty, tp, price};
                warehouse_.addBatch(std::move(batch));
            }
        } else {
            qWarning() << "Failed to load warehouse_batches:" << qb.lastError().text();
        }
    }

    // Seed from initialProducts if DB is empty (first run or no sync yet)
    if (!loadedFromDb || products_.empty()) {
        for (auto& p : initialProducts) {
            const auto id = p.id();
            if (id.empty()) {
                throw std::invalid_argument("Product id must not be empty");
            }
            auto result = products_.emplace(id, p);
            if (!result.second) {
                throw std::invalid_argument("Duplicate product id in initialProducts: " + id);
            }

            if (db.isOpen()) {
                QSqlQuery ins(db);
                ins.prepare(QStringLiteral(
                    "INSERT OR IGNORE INTO warehouse_products "
                    "(id, name, unit, is_in_stop_list) "
                    "VALUES (:id, :name, :unit, :stop)"));
                ins.bindValue(QStringLiteral(":id"), QString::fromStdString(p.id()));
                ins.bindValue(QStringLiteral(":name"), QString::fromStdString(p.name()));
                ins.bindValue(QStringLiteral(":unit"), unitToInt(p.unit()));
                ins.bindValue(QStringLiteral(":stop"), p.isInStopList() ? 1 : 0);
                if (!ins.exec()) {
                    qWarning() << "Failed to seed warehouse_products:" << ins.lastError().text();
                }
            }
        }
    }
}

void WarehouseService::addProductBatch(const std::string& productId,
                                       const Quantity& quantity,
                                       const Money& purchasePrice) {
    ensurePositiveQuantity(quantity);
    (void)requireExistingProduct(productId);

    const auto now = std::chrono::system_clock::now();
    StockBatch batch{productId, quantity, now, purchasePrice};
    warehouse_.addBatch(std::move(batch));
    syncBatchesToDatabase(warehouse_);
}

bool WarehouseService::writeOffProduct(const std::string& productId,
                                       const Quantity& quantity) {
    ensurePositiveQuantity(quantity);
    (void)requireExistingProduct(productId);

    try {
        warehouse_.consumeFifo(productId, quantity);
        syncBatchesToDatabase(warehouse_);
        return true;
    } catch (const std::runtime_error&) {
        return false;
    }
}

Quantity WarehouseService::getAvailableQuantity(const std::string& productId) const {
    (void)requireExistingProduct(productId);
    return warehouse_.totalQuantity(productId);
}

Money WarehouseService::getAveragePurchasePrice(const std::string& productId) const {
    (void)requireExistingProduct(productId);

    const auto& batches = warehouse_.batches();
    Money totalCost = Money::zero("RUB");
    Quantity totalQuantity = Quantity::zero();

    for (const auto& batch : batches) {
        if (batch.productId() == productId && batch.quantity().value() > 0.0) {
            const double qty = batch.quantity().value();
            const std::int64_t pricePerUnit = batch.purchasePrice().minorUnits();
            const std::int64_t totalBatchCost = static_cast<std::int64_t>(std::llround(pricePerUnit * qty));
            totalCost = totalCost + Money{totalBatchCost, "RUB"};
            totalQuantity = totalQuantity + batch.quantity();
        }
    }

    if (totalQuantity.value() == 0.0) {
        return Money::zero("RUB");
    }

    const double avgPrice = static_cast<double>(totalCost.minorUnits()) / totalQuantity.value();
    return Money{static_cast<std::int64_t>(std::llround(avgPrice)), "RUB"};
}

std::vector<Product> WarehouseService::getAllProducts() const {
    std::vector<Product> result;
    result.reserve(products_.size());
    for (const auto& kv : products_) {
        result.push_back(kv.second);
    }
    return result;
}

void WarehouseService::setStopList(const std::string& productId, bool enabled) {
    auto& product = requireExistingProduct(productId);
    product.setIsInStopList(enabled);
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral(
            "UPDATE warehouse_products SET is_in_stop_list = :stop WHERE id = :id"));
        q.bindValue(QStringLiteral(":stop"), enabled ? 1 : 0);
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(productId));
        if (!q.exec()) {
            qWarning() << "Failed to update stop list:" << q.lastError().text();
        }
    }
}

void WarehouseService::createProduct(const std::string& productId,
                                      const std::string& name,
                                      Unit unit) {
    if (productId.empty()) {
        throw std::invalid_argument("Product id must not be empty");
    }
    if (name.empty()) {
        throw std::invalid_argument("Product name must not be empty");
    }

    auto it = products_.find(productId);
    if (it != products_.end()) {
        throw std::invalid_argument("Product with id already exists: " + productId);
    }

    Product newProduct{productId, name, unit, false};
    products_.emplace(productId, newProduct);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral(
            "INSERT INTO warehouse_products (id, name, unit, is_in_stop_list) "
            "VALUES (:id, :name, :unit, 0)"));
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(productId));
        q.bindValue(QStringLiteral(":name"), QString::fromStdString(name));
        q.bindValue(QStringLiteral(":unit"), unitToInt(unit));
        if (!q.exec()) {
            qWarning() << "Failed to insert warehouse_product:" << q.lastError().text();
        }
    }
}

void WarehouseService::deleteProduct(const std::string& productId) {
    (void)requireExistingProduct(productId);
    warehouse_.removeBatchesForProduct(productId);
    products_.erase(productId);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral("DELETE FROM warehouse_products WHERE id = :id"));
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(productId));
        if (!q.exec()) {
            qWarning() << "Failed to delete warehouse_product:" << q.lastError().text();
        }

        QSqlQuery qb(db);
        qb.prepare(QStringLiteral("DELETE FROM warehouse_batches WHERE product_id = :id"));
        qb.bindValue(QStringLiteral(":id"), QString::fromStdString(productId));
        if (!qb.exec()) {
            qWarning() << "Failed to delete warehouse_batches for product:" << qb.lastError().text();
        }
    }
}

Product& WarehouseService::requireExistingProduct(const std::string& productId) {
    auto it = products_.find(productId);
    if (it == products_.end()) {
        throw std::invalid_argument("Unknown productId: " + productId);
    }
    return it->second;
}

const Product& WarehouseService::requireExistingProduct(const std::string& productId) const {
    auto it = products_.find(productId);
    if (it == products_.end()) {
        throw std::invalid_argument("Unknown productId: " + productId);
    }
    return it->second;
}

} // namespace domain
