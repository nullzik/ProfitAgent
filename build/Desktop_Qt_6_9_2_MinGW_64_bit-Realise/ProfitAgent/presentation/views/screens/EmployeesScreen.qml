import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: employeesScreen
    color: "#F5F5F5"

    property string selectedEmployeeId: ""
    property string selectedEmployeeName: ""
    property bool isBonusOperation: true
    property string deleteEmployeeId: ""
    property string deleteEmployeeName: ""

    CreateEmployeeDialog {
        id: createEmployeeDialog
    }

    EditEmployeeDialog {
        id: editEmployeeDialog
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            Text {
                text: "Сотрудники"
                font.pixelSize: 28
                font.bold: true
                color: "#1E1E2E"
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "+ Добавить сотрудника"
                onClicked: createEmployeeDialog.open()
                background: Rectangle {
                    color: parent.hovered ? "#2196F3" : "#1976D2"
                    radius: 8
                }
                contentItem: Text {
                    text: parent.text
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }
            }
        }

        Text {
            visible: employeeViewModel.lastError.length > 0
            text: employeeViewModel.lastError
            color: "#F44336"
            font.pixelSize: 12
            wrapMode: Text.Wrap
            Layout.fillWidth: true
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

                ShiftPanel {
                    id: managerShiftPanel
                    Layout.fillWidth: true
                    Layout.preferredHeight: 120
                    isEmployeeView: false
                    visible: appStateViewModel.currentRole === AppStateViewModel.Manager
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        model: employeeViewModel.employees
                        spacing: 4
                        delegate: Rectangle {
                            width: ListView.view ? ListView.view.width - 20 : parent.width - 20
                            height: 130
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"
                            radius: 6

                            ColumnLayout {
                                id: contentColumn
                                anchors.fill: parent
                                anchors.margins: 12
                                spacing: 8

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 16

                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        spacing: 2

                                        Text {
                                            text: modelData.fullName || ""
                                            font.pixelSize: 16
                                            font.bold: true
                                            color: "#1E1E2E"
                                            wrapMode: Text.WordWrap
                                            Layout.fillWidth: true
                                        }
                                        Text {
                                            text: modelData.roleName || ""
                                            font.pixelSize: 14
                                            color: "#666666"
                                        }
                                        Text {
                                            visible: (modelData.phone || "").length > 0
                                            text: modelData.phone || ""
                                            font.pixelSize: 12
                                            color: "#999999"
                                        }
                                        Text {
                                            text: "Баланс: " + (Number(modelData.salaryBalance).toFixed(2)) + " ₽"
                                            font.pixelSize: 12
                                            color: modelData.salaryBalance >= 0 ? "#4CAF50" : "#F44336"
                                        }
                                    }

                                    Text {
                                        text: modelData.hourlyRate > 0 ? (Number(modelData.hourlyRate).toFixed(2) + " ₽/ч") : ""
                                        font.pixelSize: 14
                                        color: "#4CAF50"
                                    }

                                    Text {
                                        visible: (modelData.login || "").length > 0
                                        text: "Логин: " + (modelData.login || "")
                                        font.pixelSize: 12
                                        color: "#666666"
                                    }

                                    RowLayout {
                                        spacing: 8

                                        Button {
                                        text: "Премия"
                                        onClicked: {
                                            employeesScreen.selectedEmployeeId = modelData.id
                                            employeesScreen.selectedEmployeeName = modelData.fullName
                                            employeesScreen.isBonusOperation = true
                                            adjustBalanceDialog.open()
                                        }
                                        background: Rectangle {
                                            color: parent.hovered ? "#2E7D32" : "#4CAF50"
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

                                    Button {
                                        text: "Штраф"
                                        onClicked: {
                                            employeesScreen.selectedEmployeeId = modelData.id
                                            employeesScreen.selectedEmployeeName = modelData.fullName
                                            employeesScreen.isBonusOperation = false
                                            adjustBalanceDialog.open()
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

                                    Button {
                                        text: "Изменить"
                                        Layout.alignment: Qt.AlignRight
                                        onClicked: {
                                            editEmployeeDialog.employeeId = modelData.id
                                            editEmployeeDialog.open()
                                        }
                                        background: Rectangle {
                                            color: parent.hovered ? "#1976D2" : "#2196F3"
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

                                    Button {
                                        text: "Удалить"
                                        onClicked: {
                                            employeesScreen.deleteEmployeeId = modelData.id
                                            employeesScreen.deleteEmployeeName = modelData.fullName || ""
                                            deleteEmployeeDialog.open()
                                        }
                                        background: Rectangle {
                                            color: parent.hovered ? "#B71C1C" : "#D32F2F"
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
                }

                Text {
                    text: "Нет сотрудников"
                    font.pixelSize: 14
                    color: "#999999"
                    Layout.alignment: Qt.AlignCenter
                    visible: employeeViewModel.employees.length === 0
                }
            }
        }
    }

    Dialog {
        id: adjustBalanceDialog
        modal: true
        title: (employeesScreen.isBonusOperation ? "Премия для " : "Штраф для ") + employeesScreen.selectedEmployeeName
        width: 360

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Text {
                    text: employeesScreen.isBonusOperation
                          ? "Введите сумму премии (₽):"
                          : "Введите сумму штрафа (₽):"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: adjustAmountField
                    Layout.fillWidth: true
                    placeholderText: "Например: 1000"
                    inputMethodHints: Qt.ImhPreferNumbers
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
                        onClicked: adjustBalanceDialog.close()
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

                    Button {
                        text: "Сохранить"
                        onClicked: {
                            const raw = adjustAmountField.text.trim()
                            if (raw.length === 0)
                                return
                            const amount = Number(raw)
                            if (!employeesScreen.selectedEmployeeId || isNaN(amount) || amount <= 0)
                                return

                            const delta = employeesScreen.isBonusOperation ? amount : -amount
                            const ok = employeeViewModel.adjustSalaryBalance(employeesScreen.selectedEmployeeId, delta)
                            if (ok) {
                                const title = (employeesScreen.isBonusOperation ? "Премия: " : "Штраф: ") + employeesScreen.selectedEmployeeName
                                const details = (employeesScreen.isBonusOperation ? "Премия " : "Штраф ")
                                        + employeesScreen.selectedEmployeeName
                                        + " на " + amount.toFixed(2) + " ₽"
                                dashboardViewModel.logUiEvent(
                                            employeesScreen.isBonusOperation ? "Премия" : "Штраф",
                                            title,
                                            details,
                                            amount)
                                dashboardViewModel.reload()
                                adjustBalanceDialog.close()
                                adjustAmountField.text = ""
                            }
                        }
                        background: Rectangle {
                            color: parent.hovered ? "#1976D2" : "#2196F3"
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

    Dialog {
        id: deleteEmployeeDialog
        modal: true
        title: "Удалить сотрудника: " + (employeesScreen.deleteEmployeeName || "")
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            const ok = employeeViewModel.deleteEmployee(employeesScreen.deleteEmployeeId)
            if (ok) {
                shiftViewModel.refresh()
                dashboardViewModel.logUiEvent(
                            "Сотрудники",
                            "Удалён сотрудник: " + (employeesScreen.deleteEmployeeName || employeesScreen.deleteEmployeeId),
                            "",
                            0)
            }
        }

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12
            implicitWidth: 420

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 12

                Text {
                    text: "Сотрудник будет удалён без возможности восстановления."
                    font.pixelSize: 14
                    color: "#1E1E2E"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

            }
        }
    }
}
