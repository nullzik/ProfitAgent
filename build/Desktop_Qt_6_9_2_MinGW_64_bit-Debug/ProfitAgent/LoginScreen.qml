import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: loginScreen
    color: "#F5F5F5"

    ColumnLayout {
        anchors.centerIn: parent
        width: 400
        spacing: 24

        Text {
            text: "ProfitAgent"
            font.pixelSize: 32
            font.bold: true
            color: "#1E1E2E"
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: "Вход в систему"
            font.pixelSize: 18
            color: "#666666"
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            color: "#E0E0E0"
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 16

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8

                Text {
                    text: "Логин"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: loginField
                    Layout.fillWidth: true
                    height: 48
                    placeholderText: "Введите логин"
                    text: authViewModel.login
                    onTextChanged: authViewModel.login = text
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8

                Text {
                    text: "Пароль"
                    font.pixelSize: 14
                    color: "#666666"
                }

                TextField {
                    id: passwordField
                    Layout.fillWidth: true
                    height: 48
                    placeholderText: "Введите пароль"
                    echoMode: TextField.Password
                    text: authViewModel.password
                    onTextChanged: authViewModel.password = text
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8

                Text {
                    text: "Роль"
                    font.pixelSize: 14
                    color: "#666666"
                }

                ComboBox {
                    id: roleComboBox
                    Layout.fillWidth: true
                    height: 48
                    model: ["Официант", "Повар", "Менеджер", "Директор"]
                    currentIndex: authViewModel.selectedRole
                    onCurrentIndexChanged: authViewModel.selectedRole = currentIndex
                    background: Rectangle {
                        radius: 8
                        border.color: "#E0E0E0"
                        border.width: 1
                        color: "#FFFFFF"
                    }
                }
            }
        }

        Button {
            Layout.fillWidth: true
            height: 48
            text: "Войти"
            onClicked: {
                authViewModel.performLogin()
            }
            background: Rectangle {
                color: parent.hovered ? "#4A90E2" : "#5A9FE2"
                radius: 8
            }
            contentItem: Text {
                text: parent.text
                color: "#FFFFFF"
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}









