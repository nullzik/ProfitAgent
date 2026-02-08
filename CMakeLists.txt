cmake_minimum_required(VERSION 3.16)

project(ProfitAgent VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Domain layer (Clean Architecture): entities, value objects, port interfaces
# -----------------------------------------------------------------------------
add_library(domain_model STATIC
    domain/value_objects/Money.h
    domain/value_objects/Money.cpp
    domain/value_objects/Quantity.h
    domain/value_objects/Quantity.cpp

    domain/employees/Employee.h
    domain/employees/Employee.cpp

    domain/menu/Dish.h
    domain/menu/Dish.cpp
    domain/menu/Recipe.h
    domain/menu/Recipe.cpp
    domain/menu/IMenuService.h

    domain/warehouse/Product.h
    domain/warehouse/Product.cpp
    domain/warehouse/StockBatch.h
    domain/warehouse/StockBatch.cpp
    domain/warehouse/Warehouse.h
    domain/warehouse/Warehouse.cpp
    domain/warehouse/IWarehouseService.h

    domain/orders/Order.h
    domain/orders/Order.cpp

    domain/audit/OperationLog.h
    domain/audit/OperationLog.cpp

    domain/Domain.h
)

# -----------------------------------------------------------------------------
# Application layer: use case implementations (services)
# -----------------------------------------------------------------------------
add_library(application_services STATIC
    application/services/MenuService.h
    application/services/MenuService.cpp
    application/services/OrderService.h
    application/services/OrderService.cpp
    application/services/WarehouseService.h
    application/services/WarehouseService.cpp
    application/services/AuthService.h
    application/services/AuthService.cpp
    application/services/EmployeeService.h
    application/services/EmployeeService.cpp
    application/database/Database.h
    application/database/Database.cpp
)
target_link_libraries(application_services PUBLIC domain_model Qt6::Core Qt6::Sql)
target_include_directories(application_services PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(domain_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Sql)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appProfitAgent
    main.cpp
    presentation/viewmodels/AppStateViewModel.cpp
    presentation/viewmodels/AppStateViewModel.h
    presentation/viewmodels/AuthViewModel.cpp
    presentation/viewmodels/AuthViewModel.h
    presentation/viewmodels/ChefViewModel.cpp
    presentation/viewmodels/ChefViewModel.h
    presentation/viewmodels/DashboardViewModel.cpp
    presentation/viewmodels/DashboardViewModel.h
    presentation/viewmodels/MenuViewModel.cpp
    presentation/viewmodels/MenuViewModel.h
    presentation/viewmodels/NavigationViewModel.cpp
    presentation/viewmodels/NavigationViewModel.h
    presentation/viewmodels/WaiterViewModel.cpp
    presentation/viewmodels/WaiterViewModel.h
    presentation/viewmodels/WarehouseViewModel.cpp
    presentation/viewmodels/WarehouseViewModel.h
    presentation/viewmodels/EmployeeViewModel.cpp
    presentation/viewmodels/EmployeeViewModel.h
)

qt_add_qml_module(appProfitAgent
    URI ProfitAgent
    VERSION 1.0
    QML_FILES
        presentation/views/Main.qml
        presentation/views/Sidebar.qml
        presentation/views/components/KPICard.qml
        presentation/views/components/OperationsTable.qml
        presentation/views/dialogs/OperationDetailsDialog.qml
        presentation/views/dialogs/OrderEntryDialog.qml
        presentation/views/dialogs/ProductOperationDialog.qml
        presentation/views/dialogs/CreateEmployeeDialog.qml
        presentation/views/dialogs/EditEmployeeDialog.qml
        presentation/views/screens/LoginScreen.qml
        presentation/views/screens/WaiterScreen.qml
        presentation/views/screens/ChefScreen.qml
        presentation/views/screens/ManagerScreen.qml
        presentation/views/screens/MenuScreen.qml
        presentation/views/screens/WarehouseScreen.qml
        presentation/views/screens/EmployeesScreen.qml
        presentation/views/screens/FinanceScreen.qml
        presentation/views/screens/HelpScreen.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appProfitAgent PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appProfitAgent
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appProfitAgent PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(appProfitAgent
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Sql
    PRIVATE domain_model
    PRIVATE application_services
)

include(GNUInstallDirs)
install(TARGETS appProfitAgent
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
