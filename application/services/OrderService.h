#pragma once

#include <string>
#include <utility>
#include <vector>

namespace domain {
class IMenuService;
class IWarehouseService;
}

namespace application {

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

private:
    domain::IMenuService& menuService_;
    domain::IWarehouseService& warehouseService_;
};

} // namespace application
