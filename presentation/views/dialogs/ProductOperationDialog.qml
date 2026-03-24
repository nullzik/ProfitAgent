import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: productDialog
    modal: true
    title: "Операция с продуктом"
    width: 500
    height: 400

    // Для использования на экране склада:
    //  - product.id   : string
    //  - product.name : string
    property var product: null

    // Заголовок: если передали доменный продукт, показываем его имя
    property string productName: product && product.name !== undefined
                                 ? product.name
                                 : "Новый продукт"

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 24

            Text {
                text: "Название продукта"
                font.pixelSize: 14
                color: "#666666"
            }

            Text {
                text: productDialog.productName
                font.pixelSize: 20
                font.bold: true
                color: "#1E1E2E"
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#E0E0E0"
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8

                Text {
                    text: "Количество"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: quantityField
                    Layout.fillWidth: true
                    height: 48
                    placeholderText: "Введите количество"
                    text: "0"
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }

                Text {
                    text: "Цена за единицу"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: priceField
                    Layout.fillWidth: true
                    height: 48
                    placeholderText: "Введите цену, например 150.50"
                    text: "0"
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }

                Text {
                    text: "Причина списания"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: reasonField
                    Layout.fillWidth: true
                    height: 48
                    placeholderText: "Например: порча, просрочка, брак"
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                Button {
                    Layout.fillWidth: true
                    text: "Добавить (поставка)"
                    enabled: product !== null
                    onClicked: {
                        if (product) {
                            const qty = Number(quantityField.text)
                            const price = Number(priceField.text)
                            warehouseViewModel.addProductBatch(product.id, qty, price)
                            const total = qty * price
                            if (total > 0) {
                                dashboardViewModel.logUiEvent(
                                            "Поставка",
                                            "Поставка: " + product.name,
                                            qty.toFixed(2) + " ед. по " + price.toFixed(2) + " ₽",
                                            total)
                            }
                            productDialog.close()
                        }
                    }
                    background: Rectangle {
                        color: parent.hovered ? "#4CAF50" : "#5CBF60"
                        radius: 8
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#FFFFFF"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Списать"
                    enabled: product !== null
                    onClicked: {
                        if (product) {
                            const qty = Number(quantityField.text)
                            const price = Number(priceField.text)
                            const reason = reasonField.text.trim()
                            warehouseViewModel.writeOffProduct(product.id, qty, reason, price)
                            productDialog.close()
                        }
                    }
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

            Button {
                Layout.fillWidth: true
                text: "Закрыть"
                onClicked: productDialog.close()
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






