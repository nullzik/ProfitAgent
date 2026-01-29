#include "domain/value_objects/Money.h"

namespace domain {

void Money::ensureSameCurrency(const Money& other) const {
    if (currency_ != other.currency_) {
        throw std::invalid_argument("Money currency mismatch");
    }
}

Money Money::operator+(const Money& other) const {
    ensureSameCurrency(other);
    return Money{minorUnits_ + other.minorUnits_, currency_};
}

Money Money::operator-(const Money& other) const {
    ensureSameCurrency(other);
    return Money{minorUnits_ - other.minorUnits_, currency_};
}

Money& Money::operator+=(const Money& other) {
    ensureSameCurrency(other);
    minorUnits_ += other.minorUnits_;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    ensureSameCurrency(other);
    minorUnits_ -= other.minorUnits_;
    return *this;
}

bool Money::operator==(const Money& other) const noexcept {
    return minorUnits_ == other.minorUnits_ && currency_ == other.currency_;
}

bool Money::operator<(const Money& other) const {
    ensureSameCurrency(other);
    return minorUnits_ < other.minorUnits_;
}

bool Money::operator>(const Money& other) const {
    ensureSameCurrency(other);
    return minorUnits_ > other.minorUnits_;
}

} // namespace domain







