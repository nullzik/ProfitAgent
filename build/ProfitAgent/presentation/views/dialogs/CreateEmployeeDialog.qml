import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: createEmployeeDialog
    modal: true
    title: "Добавить сотрудника"
    width: 450

    property string fullName: ""
    property int age: 0
    property string phone: ""
    property string address: ""
    property int roleIndex: 0
    property double hourlyRate: 0

    onOpened: {
        fullNameField.text = ""
        ageField.value = 25
        phoneField.text = ""
        addressField.text = ""
        roleComboBox.currentIndex = 0
        hourlyRateField.value = 0
    }

    contentItem: Rectangle {
        color: "#FFFFFF"
        radius: 12

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "ФИО"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: fullNameField
                    Layout.fillWidth: true
                    placeholderText: "Иванов Иван Иванович"
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Возраст"; font.pixelSize: 14; color: "#666666" }
                SpinBox {
                    id: ageField
                    from: 18
                    to: 80
                    value: 25
                    editable: true
                    Layout.fillWidth: true
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Телефон"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: phoneField
                    Layout.fillWidth: true
                    placeholderText: "+7 (999) 123-45-67"
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Адрес"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: addressField
                    Layout.fillWidth: true
                    placeholderText: "г. Москва, ул. Примерная, 1"
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Должность"; font.pixelSize: 14; color: "#666666" }
                ComboBox {
                    id: roleComboBox
                    Layout.fillWidth: true
                    model: ["Официант", "Повар", "Менеджер", "Директор", "Кассир", "Другое"]
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Часовая ставка (₽)"; font.pixelSize: 14; color: "#666666" }
                SpinBox {
                    id: hourlyRateField
                    from: 0
                    to: 10000
                    value: 0
                    editable: true
                    Layout.fillWidth: true
                    property int decimals: 2
                    property real realValue: value / 100
                    validator: DoubleValidator { bottom: 0; top: 10000; decimals: 2 }
                }
            }

            Text {
                visible: employeeViewModel.lastError.length > 0
                text: employeeViewModel.lastError
                color: "#F44336"
                font.pixelSize: 12
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.topMargin: 8
                spacing: 12

                Item { Layout.fillWidth: true }
                Button {
                    text: "Отмена"
                    onClicked: createEmployeeDialog.close()
                    background: Rectangle { color: parent.hovered ? "#999999" : "#888888"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
                Button {
                    text: "Создать"
                    onClicked: {
                        const name = fullNameField.text.trim()
                        if (name.length === 0) return
                        createRequested(name, ageField.value, phoneField.text.trim(), addressField.text.trim(),
                                        roleComboBox.currentIndex, hourlyRateField.value / 100.0)
                        const ok = employeeViewModel.createEmployee(name, ageField.value, phoneField.text.trim(),
                                                                    addressField.text.trim(), roleComboBox.currentIndex,
                                                                    hourlyRateField.value / 100.0)
                        if (ok) createEmployeeDialog.close()
                    }
                    background: Rectangle { color: parent.hovered ? "#2E7D32" : "#4CAF50"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
            }
        }
    }
}
