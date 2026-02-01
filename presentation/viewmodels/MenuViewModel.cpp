#include "MenuViewModel.h"

#include <QVariantMap>
#include <QVariantList>
#include <QDebug>

#include <cmath>
#include <cstdint>
#include <exception>

#include "domain/menu/IMenuService.h"
#include "domain/menu/Dish.h"
#include "domain/menu/Recipe.h"
#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"

using namespace domain;

MenuViewModel::MenuViewModel(IMenuService &menuService,
                             IWarehouseService &warehouseService,
                             QObject *parent)
    : QObject(parent)
    , m_menuService(menuService)
    , m_warehouseService(warehouseService)
{
    reloadDishes();
}

void MenuViewModel::createDish(const QString &dishId,
                               const QString &name,
                               double salePrice)
{
    try {
        const std::string id = dishId.toStdString();
        const std::string nameStr = name.toStdString();

        const auto minorUnits = static_cast<std::int64_t>(std::llround(salePrice * 100.0));
        Money price{minorUnits, "RUB"};

        m_menuService.createDish(id, nameStr, price);

        reloadDishes();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "MenuViewModel::createDish failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while creating dish");
        qWarning() << "MenuViewModel::createDish failed with unknown exception";
        setLastError(msg);
    }
}

void MenuViewModel::updateDish(const QString &dishId,
                               const QString &name,
                               double salePrice,
                               bool isAvailable)
{
    try {
        const std::string id = dishId.toStdString();
        const std::string nameStr = name.toStdString();

        const auto minorUnits = static_cast<std::int64_t>(std::llround(salePrice * 100.0));
        Money price{minorUnits, "RUB"};

        m_menuService.updateDish(id, nameStr, price, isAvailable);

        reloadDishes();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "MenuViewModel::updateDish failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while updating dish");
        qWarning() << "MenuViewModel::updateDish failed with unknown exception";
        setLastError(msg);
    }
}

void MenuViewModel::deleteDish(const QString &dishId)
{
    try {
        const std::string id = dishId.toStdString();
        m_menuService.deleteDish(id);

        reloadDishes();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "MenuViewModel::deleteDish failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while deleting dish");
        qWarning() << "MenuViewModel::deleteDish failed with unknown exception";
        setLastError(msg);
    }
}

QVariantList MenuViewModel::getRecipe(const QString &dishId)
{
    QVariantList result;

    try {
        const std::string id = dishId.toStdString();
        const auto recipe = m_menuService.getRecipe(id);

        for (const auto &ingredient : recipe.ingredients()) {
            QVariantMap item;
            item.insert(QStringLiteral("productId"), QString::fromStdString(ingredient.productId));
            item.insert(QStringLiteral("quantity"), ingredient.quantityRequired.value());
            result.append(item);
        }
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "MenuViewModel::getRecipe failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while getting recipe");
        qWarning() << "MenuViewModel::getRecipe failed with unknown exception";
        setLastError(msg);
    }

    return result;
}

void MenuViewModel::setRecipe(const QString &dishId,
                              const QVariantList &ingredients)
{
    try {
        const std::string id = dishId.toStdString();

        std::vector<RecipeIngredient> recipeIngredients;
        recipeIngredients.reserve(ingredients.size());

        for (const auto &variant : ingredients) {
            const auto map = variant.toMap();
            const QString productIdStr = map.value(QStringLiteral("productId")).toString();
            const double quantity = map.value(QStringLiteral("quantity")).toDouble();

            RecipeIngredient ingredient;
            ingredient.productId = productIdStr.toStdString();
            ingredient.quantityRequired = Quantity{quantity};

            recipeIngredients.push_back(ingredient);
        }

        m_menuService.setRecipe(id, recipeIngredients);

        reloadDishes();
        setLastError(QString{});
    } catch (const std::exception &e) {
        const auto msg = QString::fromUtf8(e.what());
        qWarning() << "MenuViewModel::setRecipe failed:" << msg;
        setLastError(msg);
    } catch (...) {
        const auto msg = QStringLiteral("Unknown error while setting recipe");
        qWarning() << "MenuViewModel::setRecipe failed with unknown exception";
        setLastError(msg);
    }
}

void MenuViewModel::reloadDishes()
{
    m_dishes.clear();

    const auto allDishes = m_menuService.getAllDishes();

    for (const auto &dish : allDishes) {
        QVariantMap item;
        item.insert(QStringLiteral("id"), QString::fromStdString(dish.id()));
        item.insert(QStringLiteral("name"), QString::fromStdString(dish.name()));

        const double salePriceRubles = static_cast<double>(dish.salePrice().minorUnits()) / 100.0;
        item.insert(QStringLiteral("salePrice"), salePriceRubles);

        const auto costPrice = m_menuService.getDishCost(dish.id());
        const double costPriceRubles = static_cast<double>(costPrice.minorUnits()) / 100.0;
        item.insert(QStringLiteral("costPrice"), costPriceRubles);

        item.insert(QStringLiteral("isAvailable"), dish.isAvailable());

        m_dishes.append(item);
    }

    emit dishesChanged();
}

void MenuViewModel::setLastError(const QString &message)
{
    if (m_lastError == message)
        return;

    m_lastError = message;
    emit lastErrorChanged();
}
