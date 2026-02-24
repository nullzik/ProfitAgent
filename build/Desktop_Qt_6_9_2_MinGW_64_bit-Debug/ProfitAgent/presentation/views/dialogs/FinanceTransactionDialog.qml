import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: financeTransactionDialog
    modal: true
    width: 420

    property bool isIncome: true
    property bool isEdit: false
    property int editId: 0
    property int editType: 1
    property double editAmount: 0
    property string editCategory: ""
    property string editDescription: ""

    title: isEdit ? "Редактировать операцию" : (isIncome ? "Добавить доход" : "Добавить расход")

    onOpened: {
        if (isEdit) {
            amountField.value = editAmount
            categoryField.text = editCategory
            descriptionField.text = editDescription
        } else {
            amountField.value = 0
            categoryField.text = ""
            descriptionField.text = ""
            if (isIncome) {
                categoryField.placeholderText = "Продажа, Услуги, ..."
            } else {
                categoryField.placeholderText = "Закупка, Аренда, Зарплата, ..."
            }
        }
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
                Text { text: "Сумма (₽)"; font.pixelSize: 14; color: "#666666" }
                SpinBox {
                    id: amountField
                    from: 0
                    to: 999999999
                    value: 0
                    editable: true
                    Layout.fillWidth: true
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Категория"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: categoryField
                    Layout.fillWidth: true
                    placeholderText: "Продажа, Закупка, Аренда..."
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: "Описание (необязательно)"; font.pixelSize: 14; color: "#666666" }
                TextField {
                    id: descriptionField
                    Layout.fillWidth: true
                    placeholderText: "Комментарий к операции"
                    background: Rectangle { radius: 6; border.color: "#E0E0E0"; border.width: 1; color: "#FFFFFF" }
                }
            }

            Text {
                visible: financeViewModel.lastError.length > 0
                text: financeViewModel.lastError
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
                    onClicked: financeTransactionDialog.close()
                    background: Rectangle { color: parent.hovered ? "#999999" : "#888888"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
                Button {
                    text: isEdit ? "Сохранить" : "Добавить"
                    onClicked: {
                        const cat = categoryField.text.trim()
                        if (cat.length === 0) return
                        if (amountField.value <= 0) return

                        let ok = false
                        if (isEdit) {
                            ok = financeViewModel.updateTransaction(editId, editType, amountField.value, cat, descriptionField.text.trim())
                        } else if (isIncome) {
                            ok = financeViewModel.addIncome(amountField.value, cat, descriptionField.text.trim())
                        } else {
                            ok = financeViewModel.addExpense(amountField.value, cat, descriptionField.text.trim())
                        }
                        if (ok) financeTransactionDialog.close()
                    }
                    background: Rectangle {
                        color: parent.hovered ? (isIncome ? "#2E7D32" : "#C62828") : (isIncome ? "#4CAF50" : "#F44336")
                        radius: 8
                    }
                    contentItem: Text { text: parent.text; color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
            }
        }
    }
}
