#pragma once

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "domain/value_objects/Quantity.h"
#include "domain/warehouse/StockBatch.h"

namespace domain {

// FIFO is prepared by keeping batches in purchase order.
// We expose a simple "consumption plan" to keep logic ready for later services.
class Warehouse final {
public:
    struct ConsumptionLine final {
        std::size_t batchIndex;
        Quantity quantityFromBatch;
    };

    const std::vector<StockBatch>& batches() const noexcept { return batches_; }

    void addBatch(StockBatch batch) { batches_.push_back(std::move(batch)); }

    Quantity totalQuantity(const std::string& productId) const;

    // Does not mutate state. Returns how to consume FIFO across batches.
    // Throws if insufficient stock or negative request.
    std::vector<ConsumptionLine> prepareFifoConsumption(const std::string& productId,
                                                        Quantity quantityToConsume) const;

    // Mutates batches to reflect FIFO consumption; never allows negative remainder.
    void consumeFifo(const std::string& productId, Quantity quantityToConsume);

private:
    std::vector<StockBatch> batches_;
};

} // namespace domain



