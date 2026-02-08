#include <QCoreApplication>
#include <QGuiApplication>
#include <QLibraryInfo>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "presentation/viewmodels/AppStateViewModel.h"
#include "presentation/viewmodels/AuthViewModel.h"
#include "presentation/viewmodels/ChefViewModel.h"
#include "presentation/viewmodels/DashboardViewModel.h"
#include "presentation/viewmodels/MenuViewModel.h"
#include "presentation/viewmodels/NavigationViewModel.h"
#include "presentation/viewmodels/WaiterViewModel.h"
#include "presentation/viewmodels/WarehouseViewModel.h"
#include "presentation/viewmodels/EmployeeViewModel.h"

#include "application/database/Database.h"
#include "application/services/MenuService.h"
#include "application/services/OrderService.h"
#include "application/services/WarehouseService.h"
#include "domain/warehouse/Product.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Путь к плагинам Qt (нужен для загрузки драйвера QSQLITE)
    QCoreApplication::addLibraryPath(QLibraryInfo::path(QLibraryInfo::PluginsPath));

    // Стиль, поддерживающий кастомизацию background/contentItem (Basic, Fusion, Material).
    QQuickStyle::setStyle("Basic");

    if (!application::Database::initialize()) {
        qWarning("Failed to initialize database");
    }

    // Инициализируем доменный сервис склада с тестовым каталогом продуктов.
    std::vector<domain::Product> initialProducts{
        domain::Product{"coffee_beans", "Кофе зёрна", domain::Unit::Kilogram, false},
        domain::Product{"milk", "Молоко", domain::Unit::Liter, false},
        domain::Product{"sugar", "Сахар", domain::Unit::Kilogram, false},
        domain::Product{"flour", "Мука", domain::Unit::Kilogram, false}
    };
    domain::WarehouseService warehouseService{std::move(initialProducts)};
    
    // Инициализируем доменный сервис меню
    domain::MenuService menuService{warehouseService};

    // Инициализируем сервис заказов
    application::OrderService orderService{menuService, warehouseService};

    // Создаем ViewModels
    DashboardViewModel dashboardViewModel;
    NavigationViewModel navigationViewModel;
    AuthViewModel authViewModel;
    AppStateViewModel appStateViewModel;
    WarehouseViewModel warehouseViewModel{warehouseService};
    MenuViewModel menuViewModel{menuService, warehouseService};

    WaiterViewModel waiterViewModel;
    waiterViewModel.setOrderService(&orderService);
    waiterViewModel.setWarehouseViewModel(&warehouseViewModel);

    ChefViewModel chefViewModel;
    EmployeeViewModel employeeViewModel;

    QQmlApplicationEngine engine;
    
    // Регистрируем ViewModels в QML контексте
    engine.rootContext()->setContextProperty("dashboardViewModel", &dashboardViewModel);
    engine.rootContext()->setContextProperty("navigationViewModel", &navigationViewModel);
    engine.rootContext()->setContextProperty("authViewModel", &authViewModel);
    engine.rootContext()->setContextProperty("appStateViewModel", &appStateViewModel);
    engine.rootContext()->setContextProperty("waiterViewModel", &waiterViewModel);
    engine.rootContext()->setContextProperty("chefViewModel", &chefViewModel);
    engine.rootContext()->setContextProperty("warehouseViewModel", &warehouseViewModel);
    engine.rootContext()->setContextProperty("menuViewModel", &menuViewModel);
    engine.rootContext()->setContextProperty("employeeViewModel", &employeeViewModel);

    // Регистрируем типы для использования в QML
    qmlRegisterType<DashboardViewModel>("ProfitAgent", 1, 0, "DashboardViewModel");
    qmlRegisterType<NavigationViewModel>("ProfitAgent", 1, 0, "NavigationViewModel");
    qmlRegisterType<AuthViewModel>("ProfitAgent", 1, 0, "AuthViewModel");
    qmlRegisterType<AppStateViewModel>("ProfitAgent", 1, 0, "AppStateViewModel");
    qmlRegisterType<WaiterViewModel>("ProfitAgent", 1, 0, "WaiterViewModel");
    qmlRegisterType<ChefViewModel>("ProfitAgent", 1, 0, "ChefViewModel");
    qmlRegisterType<WarehouseViewModel>("ProfitAgent", 1, 0, "WarehouseViewModel");
    qmlRegisterType<MenuViewModel>("ProfitAgent", 1, 0, "MenuViewModel");
    qmlRegisterType<EmployeeViewModel>("ProfitAgent", 1, 0, "EmployeeViewModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ProfitAgent", "Main");

    return app.exec();
}
