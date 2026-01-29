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
                        id: productsList
                        width: parent.width
                        height: parent.height
                        clip: true
                        model: warehouseViewModel.products

                        delegate: Rectangle {
                            width: ListView.view.width
                            height: 56
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"
                            radius: 6

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12

                                ColumnLayout {
                                    spacing: 4
                                    Layout.fillWidth: true

                                    Text {
                                        text: modelData.name
                                        font.pixelSize: 14
                                        font.bold: true
                                        color: "#1E1E2E"
                                    }

                                    Text {
                                        text: {
                                            var unitStr = ""
                                            if (modelData.unit === "Kilogram") {
                                                unitStr = "кг"
                                            } else if (modelData.unit === "Gram") {
                                                unitStr = "г"
                                            } else if (modelData.unit === "Liter") {
                                                unitStr = "л"
                                            }
                                            return modelData.availableQuantity + " " + unitStr
                                        }
                                        font.pixelSize: 12
                                        color: modelData.isInStopList ? "#F44336" : "#4CAF50"
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    productOperationDialog.product = modelData
                                    productOperationDialog.open()
                                }
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
}

