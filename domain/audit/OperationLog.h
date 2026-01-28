#pragma once

#include <chrono>
#include <string>

namespace domain {

enum class OperationType {
    Create,
    Update,
    Delete,
    StockAdd,
    StockConsume,
    OrderOpen,
    OrderClose,
    Other
};

class OperationLog final {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    OperationLog(OperationType operationType,
                 std::string entityId,
                 std::string authorEmployeeId,
                 TimePoint timestamp,
                 std::string description)
        : operationType_(operationType),
          entityId_(std::move(entityId)),
          authorEmployeeId_(std::move(authorEmployeeId)),
          timestamp_(timestamp),
          description_(std::move(description)) {}

    OperationType operationType() const noexcept { return operationType_; }
    const std::string& entityId() const noexcept { return entityId_; }
    const std::string& authorEmployeeId() const noexcept { return authorEmployeeId_; }
    TimePoint timestamp() const noexcept { return timestamp_; }
    const std::string& description() const noexcept { return description_; }

private:
    OperationType operationType_{OperationType::Other};
    std::string entityId_;
    std::string authorEmployeeId_;
    TimePoint timestamp_{};
    std::string description_;
};

} // namespace domain



