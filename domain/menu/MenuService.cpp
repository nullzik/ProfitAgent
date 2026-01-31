#include "domain/menu/MenuService.h"

#include <stdexcept>
#include <utility>

namespace domain {

MenuService::MenuService(IWarehouseService& warehouseService)
    : warehouseService_(warehouseService)
{
}

void MenuService::createDish(const std::string& dishId,
                             const std::string& name,
                             const Money& salePrice) {
    if (dishId.empty()) {
        throw std::invalid_argument("Dish id must not be empty");
    }
    if (name.empty()) {
        throw std::invalid_argument("Dish name must not be empty");
    }
    
    // Check if dish already exists
    auto it = dishes_.find(dishId);
    if (it != dishes_.end()) {
        throw std::invalid_argument("Dish with id already exists: " + dishId);
    }
    
    // Generate recipeId (same as dishId for simplicity)
    const std::string recipeId = dishId;
    
    Dish newDish{dishId, name, salePrice, recipeId, true};
    dishes_.emplace(dishId, std::move(newDish));
}

std::vector<Dish> MenuService::getAllDishes() const {
    std::vector<Dish> result;
    result.reserve(dishes_.size());
    for (const auto& kv : dishes_) {
        result.push_back(kv.second);
    }
    return result;
}

Money MenuService::getDishCost(const std::string& dishId) const {
    const auto& dish = requireExistingDish(dishId);
    
    // Get recipe for this dish
    auto recipeIt = recipes_.find(dish.recipeId());
    if (recipeIt == recipes_.end()) {
        return Money::zero("RUB");
    }
    
    const auto& recipe = recipeIt->second;
    Money totalCost = Money::zero("RUB");
    
    // Calculate cost based on recipe ingredients
    for (const auto& ingredient : recipe.ingredients()) {
        // Get average purchase price for this product
        Money avgPrice = warehouseService_.getAveragePurchasePrice(ingredient.productId);
        
        // Calculate cost: average price * quantity required
        const double qty = ingredient.quantityRequired.value();
        const std::int64_t pricePerUnit = avgPrice.minorUnits();
        const std::int64_t ingredientCost = static_cast<std::int64_t>(std::llround(pricePerUnit * qty));
        
        totalCost = totalCost + Money{ingredientCost, "RUB"};
    }
    
    return totalCost;
}

void MenuService::setRecipe(const std::string& dishId,
                            const std::vector<RecipeIngredient>& ingredients) {
    const auto& dish = requireExistingDish(dishId);
    
    // Validate all products exist in warehouse
    for (const auto& ingredient : ingredients) {
        try {
            (void)warehouseService_.getAvailableQuantity(ingredient.productId);
        } catch (const std::invalid_argument&) {
            throw std::invalid_argument("Product does not exist in warehouse: " + ingredient.productId);
        }
    }
    
    Recipe recipe{dish.recipeId(), ingredients};
    recipes_.insert_or_assign(dish.recipeId(), std::move(recipe));
}

Recipe MenuService::getRecipe(const std::string& dishId) const {
    const auto& dish = requireExistingDish(dishId);
    
    auto it = recipes_.find(dish.recipeId());
    if (it == recipes_.end()) {
        // Return empty recipe
        return Recipe{dish.recipeId(), {}};
    }
    
    return it->second;
}

void MenuService::updateDish(const std::string& dishId,
                            const std::string& name,
                            const Money& salePrice,
                            bool isAvailable) {
    auto& dish = requireExistingDish(dishId);
    
    dish.setName(name);
    dish.setSalePrice(salePrice);
    dish.setIsAvailable(isAvailable);
}

void MenuService::deleteDish(const std::string& dishId) {
    const auto& dish = requireExistingDish(dishId);
    
    // Remove recipe
    recipes_.erase(dish.recipeId());
    
    // Remove dish
    dishes_.erase(dishId);
}

Dish& MenuService::requireExistingDish(const std::string& dishId) {
    auto it = dishes_.find(dishId);
    if (it == dishes_.end()) {
        throw std::invalid_argument("Unknown dishId: " + dishId);
    }
    return it->second;
}

const Dish& MenuService::requireExistingDish(const std::string& dishId) const {
    auto it = dishes_.find(dishId);
    if (it == dishes_.end()) {
        throw std::invalid_argument("Unknown dishId: " + dishId);
    }
    return it->second;
}

} // namespace domain

