import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: managerScreen
    color: "#F5F5F5"

    Row {
        anchors.fill: parent
        spacing: 0

        // Sidebar
        Sidebar {
            id: sidebar
            height: parent.height
        }

        // Content Area с навигацией (единый Dashboard)
        Rectangle {
            width: parent.width - sidebar.width
            height: parent.height
            color: "#F5F5F5"

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                // Header с кнопкой выхода
                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 80
                    Layout.leftMargin: 24
                    Layout.rightMargin: 24
                    Layout.topMargin: 24
                    spacing: 16

                    Text {
                        text: navigationViewModel.currentSection === NavigationViewModel.Dashboard ? 
                              ("Привет " + dashboardViewModel.userName + " 👋") : 
                              (navigationViewModel.currentSection === NavigationViewModel.Warehouse ? "Склад" :
                              navigationViewModel.currentSection === NavigationViewModel.Menu ? "Меню" :
                              navigationViewModel.currentSection === NavigationViewModel.Employees ? "Сотрудники" :
                              navigationViewModel.currentSection === NavigationViewModel.Finance ? "Доходы и расходы" : "Помощь")
                        font.pixelSize: 28
                        font.bold: true
                        color: "#1E1E2E"
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "Выйти"
                        onClicked: appStateViewModel.logout()
                        background: Rectangle {
                            color: parent.hovered ? "#F44336" : "#E53935"
                            radius: 8
                        }
                        contentItem: Text {
                            text: parent.text
                            color: "#FFFFFF"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                // Loader для экранов
                Loader {
                    id: contentLoader
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 24

                    function updateSource() {
                        switch (navigationViewModel.currentSection) {
                        case NavigationViewModel.Dashboard:
                            sourceComponent = dashboardComponent
                            break
                        case NavigationViewModel.Warehouse:
                            sourceComponent = warehouseComponent
                            break
                        case NavigationViewModel.Menu:
                            sourceComponent = menuComponent
                            break
                        case NavigationViewModel.Employees:
                            sourceComponent = employeesComponent
                            break
                        case NavigationViewModel.Finance:
                            sourceComponent = financeComponent
                            break
                        case NavigationViewModel.Help:
                            sourceComponent = helpComponent
                            break
                        default:
                            sourceComponent = dashboardComponent
                        }
                    }

                    Component.onCompleted: updateSource()
                }

                Connections {
                    target: navigationViewModel
                    function onCurrentSectionChanged() {
                        contentLoader.updateSource()
                    }
                }
            }
        }
    }

    Component {
        id: dashboardComponent
        ColumnLayout {
            anchors.fill: parent
            spacing: 24

            // KPI Cards
            Row {
                spacing: 20

                KPICard {
                    icon: "💰"
                    title: "Выручка"
                    value: dashboardViewModel.revenue
                }

                KPICard {
                    icon: "📈"
                    title: "Чистая прибыль"
                    value: dashboardViewModel.netProfit
                }

                KPICard {
                    icon: "🛒"
                    title: "Кол-во продаж"
                    value: dashboardViewModel.salesCount
                }
            }

            // Operations Table
            OperationsTable {
                id: operationsTableComponent
                Layout.fillWidth: true
                Layout.fillHeight: true
                onOperationClicked: function(name, type, sender, date, details, amount) {
                    activityDetailsDialog.operationName = name
                    activityDetailsDialog.operationType = type
                    activityDetailsDialog.operationSender = sender
                    activityDetailsDialog.operationDate = date
                    activityDetailsDialog.operationDetails = details
                    activityDetailsDialog.operationAmount = amount
                    activityDetailsDialog.open()
                }
            }
        }
    }

    Component {
        id: warehouseComponent
        WarehouseScreen {}
    }

    Component {
        id: menuComponent
        MenuScreen {}
    }

    Component {
        id: employeesComponent
        EmployeesScreen {}
    }

    Component {
        id: financeComponent
        FinanceScreen {}
    }

    Component {
        id: helpComponent
        HelpScreen {}
    }

    ActivityDetailsDialog {
        id: activityDetailsDialog
    }
}
