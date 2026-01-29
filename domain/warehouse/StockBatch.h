#pragma once

#include <chrono>
#include <string>

#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"

namespace domain {

class StockBatch final {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    StockBatch(std::string productId,
               Quantity quantity,
               TimePoint purchaseDate,
               Money purchasePrice)
        : productId_(std::move(productId)),
          quantity_(quantity),
          purchaseDate_(purchaseDate),
          purchasePrice_(std::move(purchasePrice)) {}

    const std::string& productId() const noexcept { return productId_; }
    const Quantity& quantity() const noexcept { return quantity_; }
    TimePoint purchaseDate() const noexcept { return purchaseDate_; }
    const Money& purchasePrice() const noexcept { return purchasePrice_; }

    void setQuantity(Quantity v) { quantity_ = v; } // for Warehouse consumption adjustments

private:
    std::string productId_;
    Quantity quantity_;
    TimePoint purchaseDate_;
    Money purchasePrice_;
};

} // namespace domain







