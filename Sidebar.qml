import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar
    width: 250
    color: "#1E1E2E"

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
                model: ["Главная", "Склад", "Сотрудники", "Доходы и расходы", "Помощь"]

                Rectangle {
                    width: parent.width
                    height: 48
                    color: navigationViewModel.activeMenuItem === index ? "#3B3B5C" : "transparent"
                    radius: 8

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 16
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData
                        font.pixelSize: 16
                        color: navigationViewModel.activeMenuItem === index ? "#FFFFFF" : "#B0B0B0"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: navigationViewModel.setActiveMenuItem(index)
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }

        // Нижняя часть с аватаром
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 100

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

