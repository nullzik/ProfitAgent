import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: financeScreen
    color: "#F5F5F5"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        Text {
            text: "Доходы и расходы"
            font.pixelSize: 28
            font.bold: true
            color: "#1E1E2E"
        }

        Row {
            spacing: 20

            Rectangle {
                width: 250
                height: 150
                color: "#FFFFFF"
                radius: 12
                border.color: "#E0E0E0"
                border.width: 1

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 8

                    Text {
                        text: "💰"
                        font.pixelSize: 32
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Доходы"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "1 500 000 ₽"
                        font.pixelSize: 20
                        font.bold: true
                        color: "#4CAF50"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            Rectangle {
                width: 250
                height: 150
                color: "#FFFFFF"
                radius: 12
                border.color: "#E0E0E0"
                border.width: 1

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 8

                    Text {
                        text: "📉"
                        font.pixelSize: 32
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Расходы"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "650 000 ₽"
                        font.pixelSize: 20
                        font.bold: true
                        color: "#F44336"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
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
                    text: "Последние операции"
                    font.pixelSize: 18
                    font.bold: true
                    color: "#1E1E2E"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        model: ["Доход: Продажа - 15.01.2024", "Расход: Закупка - 14.01.2024", 
                                "Доход: Продажа - 13.01.2024", "Расход: Аренда - 12.01.2024"]

                        delegate: Rectangle {
                            width: parent.width
                            height: 50
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            Text {
                                anchors.left: parent.left
                                anchors.leftMargin: 16
                                anchors.verticalCenter: parent.verticalCenter
                                text: modelData
                                font.pixelSize: 14
                                color: "#1E1E2E"
                            }
                        }
                    }
                }
            }
        }
    }
}




