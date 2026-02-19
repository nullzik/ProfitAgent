import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: shiftPanel
    color: "#E3F2FD"
    radius: 8
    border.color: "#2196F3"
    border.width: 1

    property bool isEmployeeView: true

    Component.onCompleted: {
        if (isEmployeeView && appStateViewModel.currentEmployeeId)
            shiftViewModel.setCurrentEmployeeId(appStateViewModel.currentEmployeeId)
        else if (!isEmployeeView)
            shiftViewModel.refresh()
    }

    Connections {
        target: appStateViewModel
        function onCurrentEmployeeIdChanged() {
            if (isEmployeeView && appStateViewModel.currentEmployeeId)
                shiftViewModel.setCurrentEmployeeId(appStateViewModel.currentEmployeeId)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Text {
            text: isEmployeeView ? "Моя смена" : "Открытые смены сотрудников"
            font.pixelSize: 16
            font.bold: true
            color: "#1976D2"
        }

        Text {
            visible: isEmployeeView && shiftViewModel.lastError.length > 0
            text: shiftViewModel.lastError
            font.pixelSize: 12
            color: "#C62828"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Text {
                visible: isEmployeeView && shiftViewModel.hasOpenShift
                text: "Смена начата: " + (shiftViewModel.myOpenShift.openedAtLocal || "")
                font.pixelSize: 14
                color: "#1E1E2E"
            }

            Button {
                visible: isEmployeeView && !shiftViewModel.hasOpenShift
                text: "Начать смену"
                onClicked: shiftViewModel.openShift()
                background: Rectangle {
                    color: parent.hovered ? "#1976D2" : "#2196F3"
                    radius: 6
                }
                contentItem: Text {
                    text: parent.text
                    color: "#FFFFFF"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Button {
                visible: isEmployeeView && shiftViewModel.hasOpenShift
                text: "Закрыть смену"
                onClicked: closeShiftDialog.open()
                background: Rectangle {
                    color: parent.hovered ? "#C62828" : "#E53935"
                    radius: 6
                }
                contentItem: Text {
                    text: parent.text
                    color: "#FFFFFF"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Item { Layout.fillWidth: true }
        }

        ColumnLayout {
            visible: !isEmployeeView && shiftViewModel.openShifts.length > 0
            Layout.fillWidth: true
            spacing: 8

            Repeater {
                model: shiftViewModel.openShifts

                Rectangle {
                    Layout.fillWidth: true
                    implicitHeight: 60
                    color: "#FFFFFF"
                    radius: 6
                    border.color: "#BBDEFB"

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 12

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 2

                            Text {
                                text: modelData.employeeName || ""
                                font.pixelSize: 14
                                font.bold: true
                                color: "#1E1E2E"
                            }
                            Text {
                                text: "С " + (modelData.openedAtLocal || "")
                                font.pixelSize: 12
                                color: "#666666"
                            }
                        }

                        Button {
                            text: "Закрыть"
                            onClicked: {
                                managerCloseShiftId = modelData.id
                                managerCloseEmployeeName = modelData.employeeName
                                managerCloseShiftDialog.open()
                            }
                            background: Rectangle {
                                color: parent.hovered ? "#C62828" : "#E53935"
                                radius: 6
                            }
                            contentItem: Text {
                                text: parent.text
                                color: "#FFFFFF"
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }
        }

        Text {
            visible: !isEmployeeView && shiftViewModel.openShifts.length === 0
            text: "Нет открытых смен"
            font.pixelSize: 14
            color: "#666666"
        }
    }

    property string managerCloseShiftId: ""
    property string managerCloseEmployeeName: ""

    Dialog {
        id: closeShiftDialog
        modal: true
        title: "Закрыть смену"
        width: 360
        parent: shiftPanel

        property alias closeTimeField: closeTimeField

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12
            implicitWidth: 360

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Text {
                    text: "Введите время закрытия смены:"
                    font.pixelSize: 14
                    color: "#666666"
                }
                Text {
                    text: "Формат: HH:mm (например 18:30) или dd.MM.yyyy HH:mm"
                    font.pixelSize: 11
                    color: "#999999"
                }
                TextField {
                    id: closeTimeField
                    Layout.fillWidth: true
                    placeholderText: "Например: 18:30 (пусто = сейчас)"
                    background: Rectangle {
                        radius: 6
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12
                    Item { Layout.fillWidth: true }
                    Button {
                        text: "Отмена"
                        onClicked: closeShiftDialog.close()
                        background: Rectangle { color: parent.hovered ? "#999999" : "#888888"; radius: 8 }
                        contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                    }
                    Button {
                        text: "Закрыть"
                        onClicked: {
                            const t = closeTimeField.text.trim()
                            const s = t
                            if (shiftViewModel.closeMyShift(s)) {
                                closeShiftDialog.close()
                                closeTimeField.text = ""
                            }
                        }
                        background: Rectangle { color: parent.hovered ? "#1976D2" : "#2196F3"; radius: 8 }
                        contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                    }
                }
            }
        }
    }

    Dialog {
        id: managerCloseShiftDialog
        modal: true
        title: "Закрыть смену: " + managerCloseEmployeeName
        width: 360
        parent: shiftPanel

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12
            implicitWidth: 360

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Text {
                    text: "Введите время закрытия смены:"
                    font.pixelSize: 14
                    color: "#666666"
                }
                Text {
                    text: "Формат: HH:mm или dd.MM.yyyy HH:mm"
                    font.pixelSize: 11
                    color: "#999999"
                }
                TextField {
                    id: managerCloseTimeField
                    Layout.fillWidth: true
                    placeholderText: "Например: 18:30 (пусто = сейчас)"
                    background: Rectangle {
                        radius: 6
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12
                    Item { Layout.fillWidth: true }
                    Button {
                        text: "Отмена"
                        onClicked: managerCloseShiftDialog.close()
                        background: Rectangle { color: parent.hovered ? "#999999" : "#888888"; radius: 8 }
                        contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                    }
                    Button {
                        text: "Закрыть"
                        onClicked: {
                            const t = managerCloseTimeField.text.trim()
                            const s = t
                            if (shiftViewModel.closeShiftForEmployee(managerCloseShiftId, s)) {
                                managerCloseShiftDialog.close()
                                managerCloseTimeField.text = ""
                                employeeViewModel.reloadEmployees()
                            }
                        }
                        background: Rectangle { color: parent.hovered ? "#1976D2" : "#2196F3"; radius: 8 }
                        contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                    }
                }
            }
        }
    }
}
