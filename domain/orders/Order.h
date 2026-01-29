#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"

namespace domain {

enum class OrderStatus {
    Open,
    Closed
};

struct OrderItem final {
    std::string dishId;
    Quantity quantity;
    Money priceAtSale;
};

class Order final {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    Order(std::string id,
          std::string tableId,
          std::string waiterId,
          std::vector<OrderItem> items,
          OrderStatus status,
          TimePoint createdAt)
        : id_(std::move(id)),
          tableId_(std::move(tableId)),
          waiterId_(std::move(waiterId)),
          items_(std::move(items)),
          status_(status),
          createdAt_(createdAt) {}

    const std::string& id() const noexcept { return id_; }
    const std::string& tableId() const noexcept { return tableId_; }
    const std::string& waiterId() const noexcept { return waiterId_; }
    const std::vector<OrderItem>& items() const noexcept { return items_; }
    OrderStatus status() const noexcept { return status_; }
    TimePoint createdAt() const noexcept { return createdAt_; }

    void addItem(OrderItem item) { items_.push_back(std::move(item)); }
    void setStatus(OrderStatus v) noexcept { status_ = v; }

private:
    std::string id_;
    std::string tableId_;
    std::string waiterId_;
    std::vector<OrderItem> items_;
    OrderStatus status_{OrderStatus::Open};
    TimePoint createdAt_{};
};

} // namespace domain







