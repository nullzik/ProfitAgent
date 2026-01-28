#pragma once

#include <string>

#include "domain/value_objects/Money.h"

namespace domain {

class Dish final {
public:
    Dish(std::string id,
         std::string name,
         Money salePrice,
         std::string recipeId,
         bool isAvailable)
        : id_(std::move(id)),
          name_(std::move(name)),
          salePrice_(std::move(salePrice)),
          recipeId_(std::move(recipeId)),
          isAvailable_(isAvailable) {}

    const std::string& id() const noexcept { return id_; }
    const std::string& name() const noexcept { return name_; }
    const Money& salePrice() const noexcept { return salePrice_; }
    const std::string& recipeId() const noexcept { return recipeId_; }
    bool isAvailable() const noexcept { return isAvailable_; }

    void setName(std::string v) { name_ = std::move(v); }
    void setSalePrice(Money v) { salePrice_ = std::move(v); }
    void setRecipeId(std::string v) { recipeId_ = std::move(v); }
    void setIsAvailable(bool v) noexcept { isAvailable_ = v; }

private:
    std::string id_;
    std::string name_;
    Money salePrice_;
    std::string recipeId_;
    bool isAvailable_{true};
};

} // namespace domain



