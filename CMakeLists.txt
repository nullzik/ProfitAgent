cmake_minimum_required(VERSION 3.16)

project(ProfitAgent VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

    domain/warehouse/Product.h
    domain/warehouse/Product.cpp
    domain/warehouse/StockBatch.h
    domain/warehouse/StockBatch.cpp
    domain/warehouse/Warehouse.h
    domain/warehouse/Warehouse.cpp
    domain/warehouse/IWarehouseService.h
    domain/warehouse/WarehouseService.h
    domain/warehouse/WarehouseService.cpp

    domain/orders/Order.h
    domain/orders/Order.cpp

    domain/audit/OperationLog.h
    domain/audit/OperationLog.cpp

    domain/Domain.h
)

target_include_directories(domain_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appProfitAgent
    main.cpp
    DashboardViewModel.cpp
    DashboardViewModel.h
    NavigationViewModel.cpp
    NavigationViewModel.h
    AuthViewModel.cpp
    AuthViewModel.h
    AppStateViewModel.cpp
    AppStateViewModel.h
    WaiterViewModel.cpp
    WaiterViewModel.h
    ChefViewModel.cpp
    ChefViewModel.h
    WarehouseViewModel.cpp
    WarehouseViewModel.h
)

qt_add_qml_module(appProfitAgent
    URI ProfitAgent
    VERSION 1.0
    QML_FILES
        Main.qml
        Sidebar.qml
        KPICard.qml
        OperationsTable.qml
        OperationDetailsDialog.qml
        LoginScreen.qml
        WaiterScreen.qml
        ChefScreen.qml
        ManagerScreen.qml
        DirectorScreen.qml
        OrderEntryDialog.qml
        ProductOperationDialog.qml
        WarehouseScreen.qml
        EmployeesScreen.qml
        FinanceScreen.qml
        HelpScreen.qml
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

target_link_libraries(appProfitAgent
    PRIVATE Qt6::Quick
    PRIVATE domain_model
)

include(GNUInstallDirs)
install(TARGETS appProfitAgent
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
