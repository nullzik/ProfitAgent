import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: helpScreen
    color: "#F5F5F5"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        Text {
            text: "Помощь"
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
                    text: "Справка по системе"
                    font.pixelSize: 18
                    font.bold: true
                    color: "#1E1E2E"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ColumnLayout {
                        width: parent.width
                        spacing: 16

                        Text {
                            text: "Добро пожаловать в систему ProfitAgent!"
                            font.pixelSize: 16
                            font.bold: true
                            color: "#1E1E2E"
                        }

                        Text {
                            text: "Это система управления рестораном. Здесь вы можете:\n\n" +
                                  "• Управлять заказами\n" +
                                  "• Контролировать склад\n" +
                                  "• Просматривать финансовые отчеты\n" +
                                  "• Управлять сотрудниками"
                            font.pixelSize: 14
                            color: "#666666"
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Для получения дополнительной помощи обратитесь к администратору."
                            font.pixelSize: 14
                            color: "#999999"
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}





