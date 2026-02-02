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
                        model: 12

                        Rectangle {
                            width: 120
                            height: 80
                            color: index % 3 === 0 ? "#E8F5E9" : "#FFF3E0"
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1

                            Column {
                                anchors.centerIn: parent
                                spacing: 4

                                Text {
                                    text: "Стол " + (index + 1)
                                    font.pixelSize: 14
                                    font.bold: true
                                    color: "#1E1E2E"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

                                Text {
                                    text: index % 3 === 0 ? "Свободен" : "Занят"
                                    font.pixelSize: 12
                                    color: index % 3 === 0 ? "#4CAF50" : "#FF9800"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: waiterViewModel.onTableSelected(index)
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

