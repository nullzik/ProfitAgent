import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: employeesScreen
    color: "#F5F5F5"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        Text {
            text: "Сотрудники"
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
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Text {
                    text: "Список сотрудников"
                    font.pixelSize: 18
                    font.bold: true
                    color: "#1E1E2E"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        model: ["Иван Иванов - Официант", "Петр Петров - Повар", 
                                "Мария Сидорова - Менеджер", "Алексей Козлов - Официант"]

                        delegate: Rectangle {
                            width: parent.width
                            height: 60
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 16

                                Text {
                                    text: modelData
                                    font.pixelSize: 14
                                    color: "#1E1E2E"
                                }

                                Item {
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: "Активен"
                                    font.pixelSize: 12
                                    color: "#4CAF50"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}









