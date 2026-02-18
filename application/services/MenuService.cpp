#include "application/services/MenuService.h"

#include <stdexcept>
#include <utility>
#include <unordered_map>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

namespace domain {

MenuService::MenuService(IWarehouseService& warehouseService)
    : warehouseService_(warehouseService)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        return;
    }

    // Load dishes
    QSqlQuery q(db);
    if (q.exec(QStringLiteral(
            "SELECT id, name, sale_price_minor_units, recipe_id, is_available "
            "FROM menu_dishes"))) {
        while (q.next()) {
            const auto id = q.value(0).toString().toStdString();
            const auto name = q.value(1).toString().toStdString();
            const auto priceMinor = static_cast<std::int64_t>(q.value(2).toLongLong());
            const auto recipeId = q.value(3).toString().toStdString();
            const bool isAvailable = q.value(4).toInt() != 0;

            Money price{priceMinor, "RUB"};
            Dish dish{id, name, price, recipeId, isAvailable};
            dishes_.emplace(id, std::move(dish));
        }
    } else {
        qWarning() << "Failed to load menu_dishes:" << q.lastError().text();
    }

    // Load recipes
    QSqlQuery qr(db);
    if (qr.exec(QStringLiteral(
            "SELECT recipe_id, product_id, quantity "
            "FROM menu_recipe_ingredients "
            "ORDER BY id ASC"))) {
        std::unordered_map<std::string, std::vector<RecipeIngredient>> grouped;
        while (qr.next()) {
            const auto recipeId = qr.value(0).toString().toStdString();
            const auto productId = qr.value(1).toString().toStdString();
            const double quantity = qr.value(2).toDouble();

            RecipeIngredient ing;
            ing.productId = productId;
            ing.quantityRequired = Quantity{quantity};

            grouped[recipeId].push_back(ing);
        }

        for (auto& [recipeId, ings] : grouped) {
            recipes_.insert_or_assign(recipeId, Recipe{recipeId, std::move(ings)});
        }
    } else {
        qWarning() << "Failed to load menu_recipe_ingredients:" << qr.lastError().text();
    }
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

    auto it = dishes_.find(dishId);
    if (it != dishes_.end()) {
        throw std::invalid_argument("Dish with id already exists: " + dishId);
    }

    const std::string recipeId = dishId;
    Dish newDish{dishId, name, salePrice, recipeId, true};
    dishes_.emplace(dishId, newDish);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral(
            "INSERT INTO menu_dishes (id, name, sale_price_minor_units, recipe_id, is_available) "
            "VALUES (:id, :name, :price, :recipe_id, 1)"));
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(dishId));
        q.bindValue(QStringLiteral(":name"), QString::fromStdString(name));
        q.bindValue(QStringLiteral(":price"), static_cast<qint64>(salePrice.minorUnits()));
        q.bindValue(QStringLiteral(":recipe_id"), QString::fromStdString(recipeId));
        if (!q.exec()) {
            qWarning() << "Failed to insert menu_dish:" << q.lastError().text();
        }
    }
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

    auto recipeIt = recipes_.find(dish.recipeId());
    if (recipeIt == recipes_.end()) {
        return Money::zero("RUB");
    }

    const auto& recipe = recipeIt->second;
    Money totalCost = Money::zero("RUB");

    for (const auto& ingredient : recipe.ingredients()) {
        Money avgPrice = warehouseService_.getAveragePurchasePrice(ingredient.productId);
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

    for (const auto& ingredient : ingredients) {
        try {
            (void)warehouseService_.getAvailableQuantity(ingredient.productId);
        } catch (const std::invalid_argument&) {
            throw std::invalid_argument("Product does not exist in warehouse: " + ingredient.productId);
        }
    }

    Recipe recipe{dish.recipeId(), ingredients};
    recipes_.insert_or_assign(dish.recipeId(), recipe);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery del(db);
        del.prepare(QStringLiteral(
            "DELETE FROM menu_recipe_ingredients WHERE recipe_id = :recipe_id"));
        del.bindValue(QStringLiteral(":recipe_id"), QString::fromStdString(dish.recipeId()));
        if (!del.exec()) {
            qWarning() << "Failed to delete old recipe ingredients:" << del.lastError().text();
        }

        QSqlQuery ins(db);
        ins.prepare(QStringLiteral(
            "INSERT INTO menu_recipe_ingredients (recipe_id, product_id, quantity) "
            "VALUES (:recipe_id, :product_id, :quantity)"));

        for (const auto& ing : ingredients) {
            ins.bindValue(QStringLiteral(":recipe_id"), QString::fromStdString(dish.recipeId()));
            ins.bindValue(QStringLiteral(":product_id"), QString::fromStdString(ing.productId));
            ins.bindValue(QStringLiteral(":quantity"), ing.quantityRequired.value());
            if (!ins.exec()) {
                qWarning() << "Failed to insert recipe ingredient:" << ins.lastError().text();
            }
        }
    }
}

Recipe MenuService::getRecipe(const std::string& dishId) const {
    const auto& dish = requireExistingDish(dishId);

    auto it = recipes_.find(dish.recipeId());
    if (it == recipes_.end()) {
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

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral(
            "UPDATE menu_dishes "
            "SET name = :name, sale_price_minor_units = :price, is_available = :available "
            "WHERE id = :id"));
        q.bindValue(QStringLiteral(":name"), QString::fromStdString(name));
        q.bindValue(QStringLiteral(":price"), static_cast<qint64>(salePrice.minorUnits()));
        q.bindValue(QStringLiteral(":available"), isAvailable ? 1 : 0);
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(dishId));
        if (!q.exec()) {
            qWarning() << "Failed to update menu_dish:" << q.lastError().text();
        }
    }
}

void MenuService::deleteDish(const std::string& dishId) {
    const auto& dish = requireExistingDish(dishId);
    recipes_.erase(dish.recipeId());
    dishes_.erase(dishId);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral("DELETE FROM menu_dishes WHERE id = :id"));
        q.bindValue(QStringLiteral(":id"), QString::fromStdString(dishId));
        if (!q.exec()) {
            qWarning() << "Failed to delete menu_dish:" << q.lastError().text();
        }

        QSqlQuery qr(db);
        qr.prepare(QStringLiteral(
            "DELETE FROM menu_recipe_ingredients WHERE recipe_id = :recipe_id"));
        qr.bindValue(QStringLiteral(":recipe_id"), QString::fromStdString(dish.recipeId()));
        if (!qr.exec()) {
            qWarning() << "Failed to delete recipe ingredients:" << qr.lastError().text();
        }
    }
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
