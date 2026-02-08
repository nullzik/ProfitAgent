#pragma once

#include <string>
#include <utility>
#include <vector>

#include "domain/orders/Order.h"

namespace domain {
class IMenuService;
class IWarehouseService;
}

namespace application {

struct TableDishSummary {
    std::string dishName;
    int quantity;
};

struct TableSummary {
    bool hasOrders{false};
    std::vector<TableDishSummary> dishes;
};

class OrderService {
public:
    OrderService(domain::IMenuService& menuService,
                 domain::IWarehouseService& warehouseService);

    // Places an order: validates ingredients, writes off stock (FIFO), creates Order.
    // Returns false if any ingredient is missing, in stop-list, or insufficient.
    // On failure, no write-off is performed.
    // tableId is used for Order creation (e.g. table number).
    bool placeOrder(int tableId,
                    const std::vector<std::pair<std::string, int>>& dishes);

    // Returns summary for a table (index 0..N): has orders and list of dishes.
    TableSummary getTableSummary(int tableIndex) const;

private:
    domain::IMenuService& menuService_;
    domain::IWarehouseService& warehouseService_;
    std::vector<domain::Order> orders_;
};

} // namespace application
