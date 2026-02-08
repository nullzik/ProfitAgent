import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: employeesScreen
    color: "#F5F5F5"

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
                        model: employeeViewModel.employees
                        delegate: Rectangle {
                            width: parent.width - 20
                            height: 70
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 16
                                spacing: 16

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 4

                                    Text {
                                        text: modelData.fullName || ""
                                        font.pixelSize: 16
                                        font.bold: true
                                        color: "#1E1E2E"
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

                                Button {
                                    text: "Изменить"
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
}
