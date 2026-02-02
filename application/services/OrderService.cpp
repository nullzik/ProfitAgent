#include "application/services/OrderService.h"

#include <chrono>
#include <stdexcept>
#include <unordered_map>

#include "domain/menu/Dish.h"
#include "domain/menu/IMenuService.h"
#include "domain/menu/Recipe.h"
#include "domain/orders/Order.h"
#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"
#include "domain/warehouse/IWarehouseService.h"
#include "domain/warehouse/Product.h"

using namespace domain;

namespace application {

OrderService::OrderService(IMenuService& menuService,
                           IWarehouseService& warehouseService)
    : menuService_(menuService)
    , warehouseService_(warehouseService)
{
}

bool OrderService::placeOrder(
    int tableId,
    const std::vector<std::pair<std::string, int>>& dishes)
{
    if (dishes.empty()) {
        return false;
    }

    // 1. Aggregate required ingredients (productId -> total quantity)
    std::unordered_map<std::string, double> requiredByProduct;

    for (const auto& [dishId, count] : dishes) {
        if (count <= 0) continue;

        try {
            const Recipe recipe = menuService_.getRecipe(dishId);
            for (const auto& ing : recipe.ingredients()) {
                const double totalQty = ing.quantityRequired.value() * static_cast<double>(count);
                requiredByProduct[ing.productId] += totalQty;
            }
        } catch (const std::exception&) {
            return false; // dish not found or invalid
        }
    }

    // 2. Build stop-list map
    std::unordered_map<std::string, bool> stopListByProduct;
    for (const auto& p : warehouseService_.getAllProducts()) {
        stopListByProduct[p.id()] = p.isInStopList();
    }

    // 3. Validate: product exists, enough stock, not in stop-list
    for (const auto& [productId, requiredQty] : requiredByProduct) {
        if (requiredQty <= 0.0) continue;

        auto stopIt = stopListByProduct.find(productId);
        if (stopIt == stopListByProduct.end()) {
            return false; // product does not exist
        }
        if (stopIt->second) {
            return false; // product is in stop-list
        }

        try {
            const Quantity available = warehouseService_.getAvailableQuantity(productId);
            if (Quantity{requiredQty} > available) {
                return false; // insufficient stock
            }
        } catch (const std::invalid_argument&) {
            return false; // product does not exist
        }
    }

    // 4. Write off ingredients (FIFO)
    for (const auto& [productId, requiredQty] : requiredByProduct) {
        if (requiredQty <= 0.0) continue;

        const Quantity qty{requiredQty};
        if (!warehouseService_.writeOffProduct(productId, qty)) {
            return false; // should not happen after validation, but safety
        }
    }

    // 5. Create Order
    const auto now = std::chrono::system_clock::now();
    const std::string orderId = "order_" + std::to_string(
        static_cast<long long>(now.time_since_epoch().count()));
    const std::string tableIdStr = "table_" + std::to_string(tableId);
    const std::string waiterId = "waiter_1";

    std::vector<OrderItem> orderItems;
    orderItems.reserve(dishes.size());

    const auto allDishes = menuService_.getAllDishes();
    for (const auto& [dishId, count] : dishes) {
        if (count <= 0) continue;

        const Dish* dishPtr = nullptr;
        for (const auto& d : allDishes) {
            if (d.id() == dishId) {
                dishPtr = &d;
                break;
            }
        }
        if (!dishPtr) continue;

        OrderItem item;
        item.dishId = dishId;
        item.quantity = Quantity{static_cast<double>(count)};
        item.priceAtSale = dishPtr->salePrice();
        orderItems.push_back(std::move(item));
    }

    (void)Order{orderId, tableIdStr, waiterId, std::move(orderItems),
                OrderStatus::Open, now};

    return true;
}

} // namespace application
