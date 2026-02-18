import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: editEmployeeDialog
    modal: true
    title: "Редактировать сотрудника"
    width: 450

    property string employeeId: ""

    onEmployeeIdChanged: loadEmployee()
    onOpened: loadEmployee()

    function loadEmployee() {
        if (!employeeId) return
        const emp = employeeViewModel.getEmployeeById(employeeId)
        if (Object.keys(emp).length === 0) return
        fullNameField.text = emp.fullName || ""
        ageField.value = emp.age || 25
        phoneField.text = emp.phone || ""
        addressField.text = emp.address || ""
        roleComboBox.currentIndex = emp.role ?? 0
        hourlyRateField.value = Math.round(Number(emp.hourlyRate) || 0)
        loginField.text = emp.login || ""
        passwordField.text = ""
        passwordField.placeholderText = "Оставить пустым, чтобы не менять"
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
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Логин для входа"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: loginField
                    Layout.fillWidth: true
                    placeholderText: "Логин сотрудника"
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Новый пароль"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: passwordField
                    Layout.fillWidth: true
                    placeholderText: "Оставить пустым, чтобы не менять"
                    echoMode: TextField.Password
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
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
                    onClicked: editEmployeeDialog.close()
                    background: Rectangle { color: parent.hovered ? "#999999" : "#888888"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
                Button {
                    text: "Сохранить"
                    onClicked: {
                        const name = fullNameField.text.trim()
                        if (name.length === 0) return
                        const ok = employeeViewModel.updateEmployee(employeeId, name, ageField.value, phoneField.text.trim(),
                                                                     addressField.text.trim(), roleComboBox.currentIndex,
                                                                     hourlyRateField.value,
                                                                     loginField.text.trim(), passwordField.text)
                        if (ok) editEmployeeDialog.close()
                    }
                    background: Rectangle { color: parent.hovered ? "#2E7D32" : "#4CAF50"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
            }
        }
    }
}
