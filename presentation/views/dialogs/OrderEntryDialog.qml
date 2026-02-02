import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: orderDialog
    modal: true
    title: "Заказ - Стол " + (waiterViewModel.selectedTableId >= 0 ? waiterViewModel.selectedTableId + 1 : 1)
    width: 800
    height: 600

    property ListModel orderItemsModel: ListModel {}

    onOpened: {
        orderItemsModel.clear()
    }

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 20

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 20

                // Список блюд меню
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FAFAFA"
                    radius: 8
                    border.color: "#E0E0E0"
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        Text {
                            text: "Меню блюд"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#1E1E2E"
                        }

                        ScrollView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            ListView {
                                model: menuViewModel.dishes
                                delegate: Rectangle {
                                    width: parent.width - 20
                                    height: 70
                                    color: modelData.isAvailable ? (index % 2 === 0 ? "#FFFFFF" : "#FAFAFA") : "#EEEEEE"

                                    RowLayout {
                                        anchors.fill: parent
                                        anchors.margins: 12
                                        spacing: 12

                                        ColumnLayout {
                                            Layout.fillWidth: true
                                            spacing: 4

                                            Text {
                                                text: modelData.name
                                                font.pixelSize: 14
                                                color: modelData.isAvailable ? "#1E1E2E" : "#999999"
                                            }
                                            Text {
                                                text: (modelData.salePrice || 0).toFixed(0) + " ₽"
                                                font.pixelSize: 12
                                                font.bold: true
                                                color: "#4A90E2"
                                            }
                                        }

                                        SpinBox {
                                            id: qtySpinBox
                                            from: 1
                                            to: 99
                                            value: 1
                                            editable: true
                                            enabled: modelData.isAvailable
                                        }

                                        Button {
                                            text: "Добавить"
                                            enabled: modelData.isAvailable
                                            onClicked: {
                                                const dishId = modelData.id
                                                const name = modelData.name
                                                const qty = qtySpinBox.value
                                                if (qty > 0 && dishId) {
                                                    orderItemsModel.append({
                                                        dishId: dishId,
                                                        name: name,
                                                        quantity: qty
                                                    })
                                                }
                                            }
                                            background: Rectangle {
                                                color: parent.enabled && parent.hovered ? "#388E3C" : (parent.enabled ? "#4CAF50" : "#CCCCCC")
                                                radius: 6
                                            }
                                            contentItem: Text {
                                                text: parent.text
                                                color: "#FFFFFF"
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Позиции заказа
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FAFAFA"
                    radius: 8
                    border.color: "#E0E0E0"
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        Text {
                            text: "Позиции заказа"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#1E1E2E"
                        }

                        ScrollView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            ListView {
                                model: orderItemsModel
                                delegate: Rectangle {
                                    width: parent.width - 20
                                    height: 50
                                    color: "#FFFFFF"

                                    RowLayout {
                                        anchors.fill: parent
                                        anchors.margins: 12

                                        Text {
                                            text: model.name + " × " + model.quantity
                                            font.pixelSize: 14
                                            color: "#1E1E2E"
                                            Layout.fillWidth: true
                                        }

                                        Button {
                                            text: "✕"
                                            implicitWidth: 36
                                            onClicked: orderItemsModel.remove(index)
                                            background: Rectangle {
                                                color: parent.hovered ? "#F44336" : "#E57373"
                                                radius: 4
                                            }
                                            contentItem: Text {
                                                text: parent.text
                                                color: "#FFFFFF"
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Text {
                            text: "Заказ пуст"
                            font.pixelSize: 14
                            color: "#999999"
                            Layout.alignment: Qt.AlignCenter
                            visible: orderItemsModel.count === 0
                        }
                    }
                }
            }

            // Сообщение об ошибке/успехе
            Rectangle {
                Layout.fillWidth: true
                height: 36
                color: waiterViewModel.orderMessage ? (orderMessageIsError ? "#FFEBEE" : "#E8F5E9") : "transparent"
                radius: 6
                visible: waiterViewModel.orderMessage.length > 0

                property bool orderMessageIsError: waiterViewModel.orderMessage.indexOf("Недостаточно") >= 0

                Text {
                    anchors.centerIn: parent
                    text: waiterViewModel.orderMessage
                    font.pixelSize: 14
                    color: parent.orderMessageIsError ? "#C62828" : "#2E7D32"
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Button {
                    text: "Подтвердить заказ"
                    enabled: orderItemsModel.count > 0
                    onClicked: {
                        const items = []
                        for (let i = 0; i < orderItemsModel.count; i++) {
                            const item = orderItemsModel.get(i)
                            items.push({ dishId: item.dishId, quantity: item.quantity })
                        }
                        const ok = waiterViewModel.placeOrder(items)
                        if (ok) {
                            waiterViewModel.closeOrderEntry()
                        }
                    }
                    background: Rectangle {
                        color: parent.enabled && parent.hovered ? "#2E7D32" : (parent.enabled ? "#4CAF50" : "#CCCCCC")
                        radius: 8
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#FFFFFF"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: "Закрыть"
                    onClicked: waiterViewModel.closeOrderEntry()
                    background: Rectangle {
                        color: parent.hovered ? "#999999" : "#888888"
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
        }
    }
}
