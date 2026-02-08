import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: waiterScreen
    color: "#F5F5F5"

    // Toast при успешном заказе
    Rectangle {
        id: orderToast
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        width: 200
        height: 48
        radius: 8
        color: "#4CAF50"
        visible: false
        z: 1000

        Text {
            anchors.centerIn: parent
            text: "Заказ принят"
            font.pixelSize: 14
            color: "#FFFFFF"
        }
    }

    Connections {
        target: waiterViewModel
        function onOrderPlacedSuccess() {
            orderToast.visible = true
            toastHideTimer.restart()
        }
    }

    Timer {
        id: toastHideTimer
        interval: 3000
        repeat: false
        onTriggered: orderToast.visible = false
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header с кнопкой выхода
        RowLayout {
            Layout.fillWidth: true

            Text {
                text: "Экран официанта"
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

        // Столы
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
                    text: "Столы"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#1E1E2E"
                }

                Grid {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 4
                    spacing: 16

                    Repeater {
                        model: waiterViewModel.tables

                        Rectangle {
                            width: 140
                            height: 120
                            color: modelData.hasOrders ? "#FFF3E0" : "#E8F5E9"
                            radius: 8
                            border.color: modelData.hasOrders ? "#FFB74D" : "#A5D6A7"
                            border.width: 1

                            Column {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 4

                                Text {
                                    text: "Стол " + (modelData.tableIndex + 1)
                                    font.pixelSize: 14
                                    font.bold: true
                                    color: "#1E1E2E"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

                                Text {
                                    text: modelData.hasOrders ? "Занят" : "Свободен"
                                    font.pixelSize: 12
                                    color: modelData.hasOrders ? "#F57C00" : "#4CAF50"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

                                Repeater {
                                    model: modelData.dishes || []
                                    delegate: Text {
                                        width: 120
                                        text: modelData.name + " × " + modelData.quantity
                                        font.pixelSize: 11
                                        color: "#424242"
                                        elide: Text.ElideRight
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: waiterViewModel.onTableSelected(modelData.tableIndex)
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                    }
                }
            }
        }
    }

    OrderEntryDialog {
        id: orderEntryDialog
        parent: waiterScreen
    }

    Connections {
        target: waiterViewModel
        function onIsOrderDialogOpenChanged() {
            if (waiterViewModel.isOrderDialogOpen) {
                orderEntryDialog.open()
            } else {
                orderEntryDialog.close()
            }
        }
    }
}

