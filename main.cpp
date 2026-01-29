#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DashboardViewModel.h"
#include "NavigationViewModel.h"
#include "AuthViewModel.h"
#include "AppStateViewModel.h"
#include "WaiterViewModel.h"
#include "ChefViewModel.h"
#include "WarehouseViewModel.h"

#include "domain/warehouse/WarehouseService.h"
#include "domain/warehouse/Product.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Инициализируем доменный сервис склада с тестовым каталогом продуктов.
    std::vector<domain::Product> initialProducts{
        domain::Product{"coffee_beans", "Кофе зёрна", domain::Unit::Kilogram, false},
        domain::Product{"milk", "Молоко", domain::Unit::Liter, false},
        domain::Product{"sugar", "Сахар", domain::Unit::Kilogram, false},
        domain::Product{"flour", "Мука", domain::Unit::Kilogram, false}
    };
    domain::WarehouseService warehouseService{std::move(initialProducts)};

    // Создаем ViewModels
    DashboardViewModel dashboardViewModel;
    NavigationViewModel navigationViewModel;
    AuthViewModel authViewModel;
    AppStateViewModel appStateViewModel;
    WaiterViewModel waiterViewModel;
    ChefViewModel chefViewModel;
    WarehouseViewModel warehouseViewModel{warehouseService};

    QQmlApplicationEngine engine;
    
    // Регистрируем ViewModels в QML контексте
    engine.rootContext()->setContextProperty("dashboardViewModel", &dashboardViewModel);
    engine.rootContext()->setContextProperty("navigationViewModel", &navigationViewModel);
    engine.rootContext()->setContextProperty("authViewModel", &authViewModel);
    engine.rootContext()->setContextProperty("appStateViewModel", &appStateViewModel);
    engine.rootContext()->setContextProperty("waiterViewModel", &waiterViewModel);
    engine.rootContext()->setContextProperty("chefViewModel", &chefViewModel);
    engine.rootContext()->setContextProperty("warehouseViewModel", &warehouseViewModel);

    // Регистрируем типы для использования в QML
    qmlRegisterType<DashboardViewModel>("ProfitAgent", 1, 0, "DashboardViewModel");
    qmlRegisterType<NavigationViewModel>("ProfitAgent", 1, 0, "NavigationViewModel");
    qmlRegisterType<AuthViewModel>("ProfitAgent", 1, 0, "AuthViewModel");
    qmlRegisterType<AppStateViewModel>("ProfitAgent", 1, 0, "AppStateViewModel");
    qmlRegisterType<WaiterViewModel>("ProfitAgent", 1, 0, "WaiterViewModel");
    qmlRegisterType<ChefViewModel>("ProfitAgent", 1, 0, "ChefViewModel");
    qmlRegisterType<WarehouseViewModel>("ProfitAgent", 1, 0, "WarehouseViewModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ProfitAgent", "Main");

    return app.exec();
}
