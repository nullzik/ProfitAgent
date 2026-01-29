#pragma once

#include <cmath>
#include <stdexcept>

namespace domain {

// Value Object: immutable numeric quantity (e.g. 2.5 kg, 3 pcs).
// Unit is modeled separately in Product (warehouse); here we keep it generic.
class Quantity final {
public:
    Quantity() = default;

    explicit Quantity(double value) : value_(value) {
        if (std::isnan(value_) || std::isinf(value_)) {
            throw std::invalid_argument("Quantity must be a finite number");
        }
    }

    static Quantity zero() { return Quantity{0.0}; }

    double value() const noexcept { return value_; }

    Quantity operator+(const Quantity& other) const { return Quantity{value_ + other.value_}; }
    Quantity operator-(const Quantity& other) const { return Quantity{value_ - other.value_}; }
    Quantity operator*(double k) const { return Quantity{value_ * k}; }

    Quantity& operator+=(const Quantity& other) {
        value_ += other.value_;
        return *this;
    }
    Quantity& operator-=(const Quantity& other) {
        value_ -= other.value_;
        return *this;
    }

    bool operator==(const Quantity& other) const noexcept { return value_ == other.value_; }
    bool operator!=(const Quantity& other) const noexcept { return !(*this == other); }

    bool operator<(const Quantity& other) const noexcept { return value_ < other.value_; }
    bool operator<=(const Quantity& other) const noexcept { return value_ <= other.value_; }
    bool operator>(const Quantity& other) const noexcept { return value_ > other.value_; }
    bool operator>=(const Quantity& other) const noexcept { return value_ >= other.value_; }

private:
    double value_{0.0};
};

} // namespace domain







