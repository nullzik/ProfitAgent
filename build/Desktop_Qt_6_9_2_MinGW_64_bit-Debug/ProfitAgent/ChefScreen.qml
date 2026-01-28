import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: chefScreen
    color: "#F5F5F5"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header с кнопкой выхода
        RowLayout {
            Layout.fillWidth: true

            Text {
                text: "Экран повара"
                font.pixelSize: 24
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

        // Склад
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#FFFFFF"
            radius: 12
            border.color: "#E0E0E0"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Text {
                    text: "Склад"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#1E1E2E"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        model: ["Мука - 50 кг", "Яйца - 120 шт", "Молоко - 30 л", 
                                "Мясо - 25 кг", "Овощи - 40 кг", "Специи - 5 кг"]

                        delegate: Rectangle {
                            width: parent.width
                            height: 50
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12

                                Text {
                                    text: modelData
                                    font.pixelSize: 14
                                    color: "#1E1E2E"
                                }

                                Item {
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: index < 2 ? "Низкий" : "Норма"
                                    font.pixelSize: 12
                                    color: index < 2 ? "#F44336" : "#4CAF50"
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: chefViewModel.onProductSelected(index)
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                    }
                }
            }
        }
    }

    ProductOperationDialog {
        id: productOperationDialog
        parent: chefScreen
    }

    Connections {
        target: chefViewModel
        function onIsProductDialogOpenChanged() {
            if (chefViewModel.isProductDialogOpen) {
                productOperationDialog.open()
            } else {
                productOperationDialog.close()
            }
        }
    }
}

