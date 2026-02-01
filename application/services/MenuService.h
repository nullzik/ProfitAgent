#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "domain/menu/IMenuService.h"
#include "domain/menu/Dish.h"
#include "domain/menu/Recipe.h"
#include "domain/warehouse/IWarehouseService.h"

namespace domain {

// In-memory implementation of IMenuService (application layer).
class MenuService final : public IMenuService {
public:
    explicit MenuService(IWarehouseService& warehouseService);

    void createDish(const std::string& dishId,
                   const std::string& name,
                   const Money& salePrice) override;

    std::vector<Dish> getAllDishes() const override;

    Money getDishCost(const std::string& dishId) const override;

    void setRecipe(const std::string& dishId,
                  const std::vector<RecipeIngredient>& ingredients) override;

    Recipe getRecipe(const std::string& dishId) const override;

    void updateDish(const std::string& dishId,
                   const std::string& name,
                   const Money& salePrice,
                   bool isAvailable) override;

    void deleteDish(const std::string& dishId) override;

private:
    Dish& requireExistingDish(const std::string& dishId);
    const Dish& requireExistingDish(const std::string& dishId) const;

    IWarehouseService& warehouseService_;
    std::unordered_map<std::string, Dish> dishes_;
    std::unordered_map<std::string, Recipe> recipes_;
};

} // namespace domain
