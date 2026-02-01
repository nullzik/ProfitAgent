#include "application/services/WarehouseService.h"

#include <chrono>
#include <stdexcept>
#include <utility>

#include "domain/warehouse/StockBatch.h"

namespace domain {

namespace {
void ensurePositiveQuantity(const Quantity& q) {
    if (q.value() <= 0.0) {
        throw std::invalid_argument("quantity must be greater than zero");
    }
}
} // namespace

WarehouseService::WarehouseService(std::vector<Product> initialProducts) {
    for (auto& p : initialProducts) {
        const auto id = p.id();
        if (id.empty()) {
            throw std::invalid_argument("Product id must not be empty");
        }
        auto result = products_.emplace(id, std::move(p));
        if (!result.second) {
            throw std::invalid_argument("Duplicate product id in initialProducts: " + id);
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
}

bool WarehouseService::writeOffProduct(const std::string& productId,
                                       const Quantity& quantity) {
    ensurePositiveQuantity(quantity);
    (void)requireExistingProduct(productId);

    try {
        warehouse_.consumeFifo(productId, quantity);
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
    products_.emplace(productId, std::move(newProduct));
}

void WarehouseService::deleteProduct(const std::string& productId) {
    (void)requireExistingProduct(productId);
    warehouse_.removeBatchesForProduct(productId);
    products_.erase(productId);
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
