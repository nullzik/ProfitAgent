#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace domain {

// Value Object: immutable amount of money in minor units (e.g. cents).
class Money final {
public:
    Money() = default;

    Money(std::int64_t minorUnits, std::string currency)
        : minorUnits_(minorUnits), currency_(std::move(currency)) {
        if (currency_.empty()) {
            throw std::invalid_argument("Money currency must not be empty");
        }
    }

    static Money zero(std::string currency) { return Money{0, std::move(currency)}; }

    std::int64_t minorUnits() const noexcept { return minorUnits_; }
    const std::string& currency() const noexcept { return currency_; }

    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    bool operator==(const Money& other) const noexcept;
    bool operator!=(const Money& other) const noexcept { return !(*this == other); }

    bool operator<(const Money& other) const;
    bool operator<=(const Money& other) const { return !(*this > other); }
    bool operator>(const Money& other) const;
    bool operator>=(const Money& other) const { return !(*this < other); }

private:
    void ensureSameCurrency(const Money& other) const;

    std::int64_t minorUnits_{0};
    std::string currency_{"RUB"};
};

} // namespace domain



