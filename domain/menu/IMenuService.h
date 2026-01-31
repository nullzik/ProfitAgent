#pragma once

#include <string>
#include <vector>

#include "domain/menu/Dish.h"
#include "domain/menu/Recipe.h"
#include "domain/value_objects/Money.h"
#include "domain/warehouse/IWarehouseService.h"

namespace domain {

// Pure domain/business interface for menu operations.
class IMenuService {
public:
    virtual ~IMenuService() = default;

    // Creates a new dish in the menu.
    // Preconditions:
    //  - dishId must not be empty
    //  - name must not be empty
    //  - salePrice must be valid
    //  - dish with given dishId must not already exist
    // Throws std::invalid_argument on validation errors.
    virtual void createDish(const std::string& dishId,
                           const std::string& name,
                           const Money& salePrice) = 0;

    // Returns a snapshot of all dishes.
    virtual std::vector<Dish> getAllDishes() const = 0;

    // Calculates cost price (себестоимость) for a dish based on its recipe.
    // Uses current purchase prices from warehouse batches (FIFO average).
    // Returns zero if dish has no recipe or no ingredients.
    // Throws std::invalid_argument if dish does not exist.
    virtual Money getDishCost(const std::string& dishId) const = 0;

    // Sets recipe for a dish (replaces existing recipe if any).
    // Preconditions:
    //  - dish with given dishId must exist
    //  - all productIds in ingredients must exist in warehouse
    // Throws std::invalid_argument on validation errors.
    virtual void setRecipe(const std::string& dishId,
                          const std::vector<RecipeIngredient>& ingredients) = 0;

    // Returns recipe for a dish.
    // Returns empty recipe if dish has no recipe.
    // Throws std::invalid_argument if dish does not exist.
    virtual Recipe getRecipe(const std::string& dishId) const = 0;

    // Updates dish properties.
    // Throws std::invalid_argument if dish does not exist.
    virtual void updateDish(const std::string& dishId,
                           const std::string& name,
                           const Money& salePrice,
                           bool isAvailable) = 0;

    // Deletes a dish and its recipe.
    // Throws std::invalid_argument if dish does not exist.
    virtual void deleteDish(const std::string& dishId) = 0;
};

} // namespace domain

