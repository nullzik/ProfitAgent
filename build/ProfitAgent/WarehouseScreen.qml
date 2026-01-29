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

                Text {
                    text: "Список товаров"
                    font.pixelSize: 18
                    font.bold: true
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

                                Text {
                                    text: modelData.name
                                    font.pixelSize: 14
                                }

                                Item { Layout.fillWidth: true }

                                Text {
                                    text: modelData.availableQuantity
                                    font.pixelSize: 13
                                    color: modelData.isInStopList ? "#F44336" : "#4CAF50"
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    selectedProduct = modelData
                                    productDialog.open()
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
}
