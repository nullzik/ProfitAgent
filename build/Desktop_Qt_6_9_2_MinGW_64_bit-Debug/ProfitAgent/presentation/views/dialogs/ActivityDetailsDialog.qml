import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: activityDialog
    modal: true
    title: "Детали операции"
    width: 640
    height: 440

    property string operationName: ""
    property string operationType: ""
    property string operationSender: ""
    property string operationDate: ""
    property string operationDetails: ""
    property string operationAmount: ""

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 18

            Text {
                text: activityDialog.operationName
                font.pixelSize: 20
                font.bold: true
                color: "#1E1E2E"
                Layout.fillWidth: true
                wrapMode: Text.Wrap
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#E0E0E0"
            }

            GridLayout {
                columns: 2
                columnSpacing: 24
                rowSpacing: 8
                Layout.fillWidth: true

                Text {
                    text: "Тип"
                    font.pixelSize: 12
                    color: "#666666"
                }
                Text {
                    text: activityDialog.operationType
                    font.pixelSize: 14
                    color: "#1E1E2E"
                }

                Text {
                    text: "Источник"
                    font.pixelSize: 12
                    color: "#666666"
                }
                Text {
                    text: activityDialog.operationSender
                    font.pixelSize: 14
                    color: "#1E1E2E"
                }

                Text {
                    text: "Дата и время"
                    font.pixelSize: 12
                    color: "#666666"
                }
                Text {
                    text: activityDialog.operationDate
                    font.pixelSize: 14
                    color: "#1E1E2E"
                }

                Text {
                    visible: activityDialog.operationAmount.length > 0
                    text: "Сумма"
                    font.pixelSize: 12
                    color: "#666666"
                }
                Text {
                    visible: activityDialog.operationAmount.length > 0
                    text: activityDialog.operationAmount
                    font.pixelSize: 16
                    font.bold: true
                    color: activityDialog.operationAmount.startsWith("+") ? "#4CAF50" : "#F44336"
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: activityDialog.operationDetails.length > 0 ? 1 : 0
                visible: activityDialog.operationDetails.length > 0
                color: "#E0E0E0"
            }

            ColumnLayout {
                visible: activityDialog.operationDetails.length > 0
                Layout.fillWidth: true
                spacing: 6

                Text {
                    text: "Подробности"
                    font.pixelSize: 12
                    color: "#666666"
                }

                Text {
                    text: activityDialog.operationDetails
                    font.pixelSize: 14
                    color: "#1E1E2E"
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Закрыть"
                onClicked: activityDialog.close()
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

