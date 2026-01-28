import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: productDialog
    modal: true
    title: "Операция с продуктом"
    width: 500
    height: 400

    property string productName: "Продукт " + (chefViewModel.selectedProductId + 1)

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
                    onClicked: chefViewModel.addProduct()
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
                    onClicked: chefViewModel.writeOffProduct()
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
                onClicked: chefViewModel.closeProductDialog()
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




