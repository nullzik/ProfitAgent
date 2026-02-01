import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: operationDialog
    modal: true
    title: "Детали операции"
    width: 600
    height: 400

    property string operationName: ""
    property string operationType: ""
    property string operationSender: ""
    property string operationDate: ""

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 20

            Text {
                text: "Наименование"
                font.pixelSize: 12
                color: "#666666"
            }

            Text {
                text: operationDialog.operationName
                font.pixelSize: 18
                font.bold: true
                color: "#1E1E2E"
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#E0E0E0"
            }

            Text {
                text: "Тип операции"
                font.pixelSize: 12
                color: "#666666"
            }

            Text {
                text: operationDialog.operationType
                font.pixelSize: 16
                color: "#1E1E2E"
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#E0E0E0"
            }

            Text {
                text: "Отправитель"
                font.pixelSize: 12
                color: "#666666"
            }

            Text {
                text: operationDialog.operationSender
                font.pixelSize: 16
                color: "#1E1E2E"
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#E0E0E0"
            }

            Text {
                text: "Дата"
                font.pixelSize: 12
                color: "#666666"
            }

            Text {
                text: operationDialog.operationDate
                font.pixelSize: 16
                color: "#1E1E2E"
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Закрыть"
                onClicked: operationDialog.close()
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
        }
    }
}

