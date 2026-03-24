import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar
    width: 250
    color: "#1E1E2E"
    property var menuItems: {
        // У повара скрываем "Сотрудники" и "Доходы и расходы".
        if (navigationViewModel.userRole === "Повар") {
            return [
                { text: "Главная", section: NavigationViewModel.Dashboard },
                { text: "Склад", section: NavigationViewModel.Warehouse },
                { text: "Меню", section: NavigationViewModel.Menu },
                { text: "Помощь", section: NavigationViewModel.Help }
            ]
        }
        return [
            { text: "Главная", section: NavigationViewModel.Dashboard },
            { text: "Склад", section: NavigationViewModel.Warehouse },
            { text: "Меню", section: NavigationViewModel.Menu },
            { text: "Сотрудники", section: NavigationViewModel.Employees },
            { text: "Доходы и расходы", section: NavigationViewModel.Finance },
            { text: "Помощь", section: NavigationViewModel.Help }
        ]
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Логотип
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: "#252538"

            Text {
                anchors.centerIn: parent
                text: "ProfitAgent"
                font.pixelSize: 24
                font.bold: true
                color: "#FFFFFF"
            }
        }

        // Навигация
        Column {
            Layout.fillWidth: true
            spacing: 4
            padding: 16

            Repeater {
                model: sidebar.menuItems

                Rectangle {
                    width: parent.width
                    height: 48
                    color: navigationViewModel.activeMenuItem === modelData.section ? "#3B3B5C" : "transparent"
                    radius: 8

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 16
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.text
                        font.pixelSize: 16
                        color: navigationViewModel.activeMenuItem === modelData.section ? "#FFFFFF" : "#B0B0B0"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: navigationViewModel.setActiveMenuItem(modelData.section)
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }

        // Нижняя часть с аватаром
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 50

            Rectangle {
                anchors.fill: parent
                anchors.margins: 16
                color: "#252538"
                radius: 12

                Row {
                    anchors.centerIn: parent
                    spacing: 12

                    // Аватар
                    Rectangle {
                        width: 48
                        height: 48
                        radius: 24
                        color: "#4A90E2"

                        Text {
                            anchors.centerIn: parent
                            text: navigationViewModel.userName.length > 0 ? navigationViewModel.userName[0] : "U"
                            font.pixelSize: 20
                            font.bold: true
                            color: "#FFFFFF"
                        }
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 4

                        Text {
                            text: navigationViewModel.userName
                            font.pixelSize: 14
                            font.bold: true
                            color: "#FFFFFF"
                        }

                        Text {
                            text: navigationViewModel.userRole
                            font.pixelSize: 12
                            color: "#B0B0B0"
                        }
                    }
                }
            }
        }
    }
}

