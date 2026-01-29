#pragma once

#include <string>
#include <vector>

#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"
#include "domain/warehouse/Product.h"

namespace domain {

// Pure domain/business interface for warehouse operations.
// UI and infrastructure layers are expected to depend on this interface.
class IWarehouseService {
public:
    virtual ~IWarehouseService() = default;

    // Registers arrival of a product batch into the warehouse.
    // Preconditions:
    //  - quantity.value() > 0
    //  - product with given productId exists
    // Throws std::invalid_argument on validation errors.
    virtual void addProductBatch(const std::string& productId,
                                 const Quantity& quantity,
                                 const Money& purchasePrice) = 0;

    // Writes off product from warehouse using FIFO batches.
    // Preconditions:
    //  - quantity.value() > 0
    //  - product with given productId exists
    //
    // Returns:
    //  - true  if write-off has been successfully performed
    //  - false if there is not enough stock (operation rejected, state unchanged)
    //
    // Throws std::invalid_argument on validation errors unrelated to stock level.
    virtual bool writeOffProduct(const std::string& productId,
                                 const Quantity& quantity) = 0;

    // Returns available quantity in warehouse for given product.
    // Throws std::invalid_argument if product with such id does not exist.
    virtual Quantity getAvailableQuantity(const std::string& productId) const = 0;

    // Returns a snapshot of all known products.
    virtual std::vector<Product> getAllProducts() const = 0;

    // Puts product into stop list or removes it from there.
    // Throws std::invalid_argument if product with such id does not exist.
    virtual void setStopList(const std::string& productId, bool enabled) = 0;

    // Creates a new product in the catalog.
    // Preconditions:
    //  - productId must not be empty
    //  - name must not be empty
    //  - product with given productId must not already exist
    // Throws std::invalid_argument on validation errors.
    virtual void createProduct(const std::string& productId,
                               const std::string& name,
                               Unit unit) = 0;

    // Deletes a product from the catalog.
    // Also removes all stock batches for this product.
    // Preconditions:
    //  - product with given productId must exist
    // Throws std::invalid_argument if product does not exist.
    virtual void deleteProduct(const std::string& productId) = 0;
};

} // namespace domain







