#pragma once

#include <string>
#include <vector>

#include "domain/value_objects/Quantity.h"

namespace domain {

struct RecipeIngredient final {
    std::string productId;
    Quantity quantityRequired;
};

class Recipe final {
public:
    Recipe(std::string dishId, std::vector<RecipeIngredient> ingredients)
        : dishId_(std::move(dishId)), ingredients_(std::move(ingredients)) {}

    const std::string& dishId() const noexcept { return dishId_; }
    const std::vector<RecipeIngredient>& ingredients() const noexcept { return ingredients_; }

    void setIngredients(std::vector<RecipeIngredient> v) { ingredients_ = std::move(v); }
    void addIngredient(RecipeIngredient v) { ingredients_.push_back(std::move(v)); }

private:
    std::string dishId_;
    std::vector<RecipeIngredient> ingredients_;
};

} // namespace domain



