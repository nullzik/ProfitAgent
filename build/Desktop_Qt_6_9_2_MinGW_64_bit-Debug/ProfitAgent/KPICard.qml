import QtQuick
import QtQuick.Controls

Rectangle {
    id: card
    width: 280
    height: 140
    radius: 12
    color: "#FFFFFF"
    border.color: "#E0E0E0"
    border.width: 1

    property string icon: "💰"
    property string title: ""
    property string value: ""
    property string change: ""

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Row {
            spacing: 12
            width: parent.width

            Text {
                text: card.icon
                font.pixelSize: 32
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 4

                Text {
                    text: card.title
                    font.pixelSize: 14
                    color: "#666666"
                }

                Text {
                    text: card.value
                    font.pixelSize: 24
                    font.bold: true
                    color: "#1E1E2E"
                }
            }
        }

        Row {
            spacing: 8

            Text {
                text: card.change
                font.pixelSize: 14
                color: card.change.startsWith("+") ? "#4CAF50" : "#F44336"
            }

            Text {
                text: "за период"
                font.pixelSize: 12
                color: "#999999"
            }
        }
    }
}






