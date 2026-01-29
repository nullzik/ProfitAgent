#pragma once

#include <string>

namespace domain {

enum class Unit {
    Kilogram,
    Gram,
    Liter
};

class Product final {
public:
    Product(std::string id, std::string name, Unit unit, bool isInStopList)
        : id_(std::move(id)),
          name_(std::move(name)),
          unit_(unit),
          isInStopList_(isInStopList) {}

    const std::string& id() const noexcept { return id_; }
    const std::string& name() const noexcept { return name_; }
    Unit unit() const noexcept { return unit_; }
    bool isInStopList() const noexcept { return isInStopList_; }

    void setName(std::string v) { name_ = std::move(v); }
    void setUnit(Unit v) noexcept { unit_ = v; }
    void setIsInStopList(bool v) noexcept { isInStopList_ = v; }

private:
    std::string id_;
    std::string name_;
    Unit unit_{Unit::Kilogram};
    bool isInStopList_{false};
};

} // namespace domain







