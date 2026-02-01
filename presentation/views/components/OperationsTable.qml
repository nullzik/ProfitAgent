import QtQuick
import QtQuick.Controls

Rectangle {
    id: operationsTable
    color: "#FFFFFF"
    radius: 12
    border.color: "#E0E0E0"
    border.width: 1

    signal operationClicked(string name, string type, string sender, string date)

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        // Заголовок с поиском и фильтром
        Row {
            width: parent.width
            spacing: 16

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "Последние операции"
                font.pixelSize: 20
                font.bold: true
                color: "#1E1E2E"
            }

            Item {
                width: parent.width - x
                height: 40

                Row {
                    anchors.right: parent.right
                    spacing: 12

                    // Поле поиска
                    TextField {
                        width: 200
                        height: 40
                        placeholderText: "Поиск..."
                        font.pixelSize: 14
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FAFAFA"
                        }
                    }

                    // Dropdown фильтра
                    ComboBox {
                        width: 150
                        height: 40
                        model: ["Все", "Продажа", "Закупка", "Расход"]
                        currentIndex: 0
                    }
                }
            }
        }

        // Таблица
        Rectangle {
            width: parent.width
            height: parent.height - y - 60
            color: "#FAFAFA"
            radius: 8

            ListView {
                id: listView
                anchors.fill: parent
                anchors.margins: 1
                model: dashboardViewModel.operationsModel
                clip: true

                header: Rectangle {
                    width: listView.width
                    height: 48
                    color: "#FFFFFF"
                    radius: 8

                    Row {
                        anchors.fill: parent
                        anchors.margins: 16

                        Text {
                            width: parent.width * 0.3
                            text: "Наименование"
                            font.pixelSize: 12
                            font.bold: true
                            color: "#666666"
                        }

                        Text {
                            width: parent.width * 0.2
                            text: "Тип операции"
                            font.pixelSize: 12
                            font.bold: true
                            color: "#666666"
                        }

                        Text {
                            width: parent.width * 0.25
                            text: "Отправитель"
                            font.pixelSize: 12
                            font.bold: true
                            color: "#666666"
                        }

                        Text {
                            width: parent.width * 0.15
                            text: "Дата"
                            font.pixelSize: 12
                            font.bold: true
                            color: "#666666"
                        }

                        Item {
                            width: parent.width * 0.1
                        }
                    }
                }

                delegate: Rectangle {
                    width: listView.width
                    height: 56
                    color: index % 2 === 0 ? "#FFFFFF" : "#FAFAFA"

                    Row {
                        anchors.fill: parent
                        anchors.margins: 16

                        Text {
                            width: parent.width * 0.3
                            text: model.name
                            font.pixelSize: 14
                            color: "#1E1E2E"
                            elide: Text.ElideRight
                        }

                        Text {
                            width: parent.width * 0.2
                            text: model.type
                            font.pixelSize: 14
                            color: "#1E1E2E"
                            elide: Text.ElideRight
                        }

                        Text {
                            width: parent.width * 0.25
                            text: model.sender
                            font.pixelSize: 14
                            color: "#1E1E2E"
                            elide: Text.ElideRight
                        }

                        Text {
                            width: parent.width * 0.15
                            text: model.date
                            font.pixelSize: 14
                            color: "#1E1E2E"
                        }

                        Button {
                            width: parent.width * 0.1
                            height: 32
                            text: "Перейти"
                            flat: true
                            background: Rectangle {
                                color: parent.hovered ? "#E3F2FD" : "transparent"
                                radius: 4
                            }
                            onClicked: {
                                // Сигнал для открытия окна деталей операции
                                operationsTable.operationClicked(model.name, model.type, model.sender, model.date)
                            }
                        }
                    }
                }
            }
        }

        // Пагинация
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 8

            Repeater {
                model: dashboardViewModel.totalPages

                Button {
                    width: 40
                    height: 40
                    text: (index + 1).toString()
                    flat: true
                    background: Rectangle {
                        color: dashboardViewModel.currentPage === (index + 1) ? "#4A90E2" : "transparent"
                        radius: 8
                        border.color: dashboardViewModel.currentPage === (index + 1) ? "#4A90E2" : "#E0E0E0"
                        border.width: 1
                    }
                    contentItem: Text {
                        text: parent.text
                        font.pixelSize: 14
                        color: dashboardViewModel.currentPage === (index + 1) ? "#FFFFFF" : "#1E1E2E"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: dashboardViewModel.setCurrentPage(index + 1)
                }
            }
        }
    }
}

