import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: orderDialog
    modal: true
    title: "Заказ - Стол " + (waiterViewModel.selectedTableId + 1)
    width: 800
    height: 600

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 20

            RowLayout {
                Layout.fillWidth: true
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
                                model: ["Салат Цезарь", "Борщ", "Стейк", "Пицца Маргарита", 
                                        "Паста Карбонара", "Рыба на гриле", "Десерт", "Кофе"]

                                delegate: Rectangle {
                                    width: parent.width
                                    height: 60
                                    color: index % 2 === 0 ? "#FFFFFF" : "#FAFAFA"

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
                                            text: (index + 1) * 250 + " ₽"
                                            font.pixelSize: 14
                                            font.bold: true
                                            color: "#4A90E2"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Список позиций заказа
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
                                model: [] // Пустой список

                                delegate: Rectangle {
                                    width: parent.width
                                    height: 50
                                    color: "#FFFFFF"
                                }

                                Text {
                                    anchors.centerIn: parent
                                    text: "Заказ пуст"
                                    font.pixelSize: 14
                                    color: "#999999"
                                    visible: parent.count === 0
                                }
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Button {
                    text: "Добавить блюдо"
                    onClicked: {
                        // Заглушка: без логики
                    }
                    background: Rectangle {
                        color: parent.hovered ? "#4A90E2" : "#5A9FE2"
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



