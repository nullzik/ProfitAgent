import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: warehouseScreen
    color: "#F5F5F5"

    property var selectedProduct: null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        Text {
            text: "Склад"
            font.pixelSize: 28
            font.bold: true
            color: "#1E1E2E"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#FFFFFF"
            radius: 12
            border.color: "#E0E0E0"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Text {
                        text: "Список товаров"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "+ Добавить товар"
                        onClicked: createProductDialog.open()
                        background: Rectangle {
                            color: parent.hovered ? "#2196F3" : "#1976D2"
                            radius: 8
                        }
                        contentItem: Text {
                            text: parent.text
                            color: "#FFFFFF"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 14
                        }
                    }
                }

                // Отображение последней ошибки доменного слоя (если есть)
                Text {
                    visible: warehouseViewModel.lastError.length > 0
                    text: warehouseViewModel.lastError
                    color: "#F44336"
                    font.pixelSize: 12
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
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

                                MouseArea {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        selectedProduct = modelData
                                        productDialog.open()
                                    }

                                    ColumnLayout {
                                        anchors.fill: parent
                                        spacing: 4

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

                                Button {
                                    text: "Удалить"
                                    onClicked: {
                                        warehouseViewModel.deleteProduct(modelData.id)
                                    }
                                    background: Rectangle {
                                        color: parent.hovered ? "#F44336" : "#E53935"
                                        radius: 6
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: "#FFFFFF"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: 12
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ProductOperationDialog {
        id: productDialog
        product: selectedProduct
    }

    Dialog {
        id: createProductDialog
        modal: true
        title: "Добавить новый товар"
        width: 500
        height: 450

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                Text {
                    text: "Заполните данные о новом товаре"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#1E1E2E"
                    Layout.fillWidth: true
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "ID товара (уникальный идентификатор)"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    TextField {
                        id: productIdField
                        Layout.fillWidth: true
                        height: 48
                        placeholderText: "Например: flour_1kg"
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FFFFFF"
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "Название товара"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    TextField {
                        id: productNameField
                        Layout.fillWidth: true
                        height: 48
                        placeholderText: "Например: Мука пшеничная"
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FFFFFF"
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "Единица измерения"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    ComboBox {
                        id: unitComboBox
                        Layout.fillWidth: true
                        height: 48
                        model: ["Kilogram", "Gram", "Liter"]
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
                        text: "Отмена"
                        onClicked: createProductDialog.close()
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

                    Button {
                        Layout.fillWidth: true
                        text: "Создать"
                        onClicked: {
                            const id = productIdField.text.trim()
                            const name = productNameField.text.trim()
                            const unit = unitComboBox.currentText

                            if (id.length === 0 || name.length === 0) {
                                return
                            }

                            warehouseViewModel.createProduct(id, name, unit)
                            createProductDialog.close()
                            
                            // Очистка полей
                            productIdField.text = ""
                            productNameField.text = ""
                            unitComboBox.currentIndex = 0
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
                }
            }
        }
    }
}
