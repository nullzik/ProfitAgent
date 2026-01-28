#include "domain/warehouse/Warehouse.h"

namespace domain {

Quantity Warehouse::totalQuantity(const std::string& productId) const {
    Quantity total = Quantity::zero();
    for (const auto& b : batches_) {
        if (b.productId() == productId) {
            total += b.quantity();
        }
    }
    return total;
}

std::vector<Warehouse::ConsumptionLine> Warehouse::prepareFifoConsumption(
    const std::string& productId,
    Quantity quantityToConsume) const {
    if (quantityToConsume.value() < 0.0) {
        throw std::invalid_argument("quantityToConsume must be non-negative");
    }

    if (totalQuantity(productId) < quantityToConsume) {
        throw std::runtime_error("insufficient stock");
    }

    std::vector<ConsumptionLine> plan;
    Quantity remaining = quantityToConsume;

    for (std::size_t i = 0; i < batches_.size() && remaining.value() > 0.0; ++i) {
        const auto& batch = batches_[i];
        if (batch.productId() != productId) {
            continue;
        }

        const double canTake = batch.quantity().value();
        if (canTake <= 0.0) {
            continue;
        }

        const double take = (canTake >= remaining.value()) ? remaining.value() : canTake;
        plan.push_back(ConsumptionLine{i, Quantity{take}});
        remaining -= Quantity{take};
    }

    // totalQuantity pre-check guarantees full plan, but keep guard.
    if (remaining.value() > 0.0) {
        throw std::runtime_error("failed to prepare FIFO plan");
    }

    return plan;
}

void Warehouse::consumeFifo(const std::string& productId, Quantity quantityToConsume) {
    const auto plan = prepareFifoConsumption(productId, quantityToConsume);
    for (const auto& line : plan) {
        auto& batch = batches_.at(line.batchIndex);
        const Quantity newQty = batch.quantity() - line.quantityFromBatch;
        if (newQty.value() < 0.0) {
            throw std::logic_error("negative batch quantity would occur");
        }
        batch.setQuantity(newQty);
    }
}

} // namespace domain



