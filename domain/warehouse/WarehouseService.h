#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "domain/warehouse/IWarehouseService.h"
#include "domain/warehouse/Warehouse.h"

namespace domain {

// In-memory implementation of IWarehouseService.
// Orchestrates domain entities: Product, StockBatch, Warehouse.
class WarehouseService final : public IWarehouseService {
public:
    // Constructs service with initial product catalog.
    // Product identities are taken from Product::id().
    explicit WarehouseService(std::vector<Product> initialProducts);

    void addProductBatch(const std::string& productId,
                         const Quantity& quantity,
                         const Money& purchasePrice) override;

    bool writeOffProduct(const std::string& productId,
                         const Quantity& quantity) override;

    Quantity getAvailableQuantity(const std::string& productId) const override;

    std::vector<Product> getAllProducts() const override;

    void setStopList(const std::string& productId, bool enabled) override;

    void createProduct(const std::string& productId,
                       const std::string& name,
                       Unit unit) override;

    void deleteProduct(const std::string& productId) override;

private:
    Product& requireExistingProduct(const std::string& productId);
    const Product& requireExistingProduct(const std::string& productId) const;

    std::unordered_map<std::string, Product> products_;
    Warehouse warehouse_;
};

} // namespace domain







