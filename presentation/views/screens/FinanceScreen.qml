import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: financeScreen
    color: "#F5F5F5"

    property int currentTab: 0  // 0=all, 1=income, 2=expense
    property int transactionToDelete: 0

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Text {
                text: "Доходы и расходы"
                font.pixelSize: 28
                font.bold: true
                color: "#1E1E2E"
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "+ Добавить доход"
                onClicked: {
                    addIncomeDialog.isIncome = true
                    addIncomeDialog.isEdit = false
                    addIncomeDialog.open()
                }
                background: Rectangle {
                    color: parent.hovered ? "#2E7D32" : "#4CAF50"
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

            Button {
                text: "+ Добавить расход"
                onClicked: {
                    addIncomeDialog.isIncome = false
                    addIncomeDialog.isEdit = false
                    addIncomeDialog.open()
                }
                background: Rectangle {
                    color: parent.hovered ? "#C62828" : "#F44336"
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
            visible: financeViewModel.lastError.length > 0
            text: financeViewModel.lastError
            color: "#F44336"
            font.pixelSize: 12
            wrapMode: Text.Wrap
            Layout.fillWidth: true
        }

        Row {
            spacing: 20

            Rectangle {
                width: 220
                height: 120
                color: "#FFFFFF"
                radius: 12
                border.color: "#E0E0E0"
                border.width: 1

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 6

                    Text {
                        text: "💰"
                        font.pixelSize: 28
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Доходы"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: financeViewModel.formatMoney(financeViewModel.totalIncome)
                        font.pixelSize: 18
                        font.bold: true
                        color: "#4CAF50"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            Rectangle {
                width: 220
                height: 120
                color: "#FFFFFF"
                radius: 12
                border.color: "#E0E0E0"
                border.width: 1

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 6

                    Text {
                        text: "📉"
                        font.pixelSize: 28
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Расходы"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: financeViewModel.formatMoney(financeViewModel.totalExpenses)
                        font.pixelSize: 18
                        font.bold: true
                        color: "#F44336"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            Rectangle {
                width: 220
                height: 120
                color: "#FFFFFF"
                radius: 12
                border.color: "#E0E0E0"
                border.width: 1

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 6

                    Text {
                        text: "📊"
                        font.pixelSize: 28
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Прибыль"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: financeViewModel.formatMoney(financeViewModel.profit)
                        font.pixelSize: 18
                        font.bold: true
                        color: financeViewModel.profit >= 0 ? "#2196F3" : "#F44336"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: "Все операции"
                width: implicitWidth
            }
            TabButton {
                text: "Доходы"
                width: implicitWidth
            }
            TabButton {
                text: "Расходы"
                width: implicitWidth
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
                    text: tabBar.currentIndex === 0 ? "Последние операции" :
                          (tabBar.currentIndex === 1 ? "Доходы" : "Расходы")
                    font.pixelSize: 18
                    font.bold: true
                    color: "#1E1E2E"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: transactionsList
                        width: parent.width - 20
                        clip: true
                        model: tabBar.currentIndex === 0 ? financeViewModel.transactions :
                               (tabBar.currentIndex === 1 ? financeViewModel.incomeTransactions : financeViewModel.expenseTransactions)

                        footer: Item {
                            width: transactionsList.width
                            height: transactionsList.count === 0 ? 200 : 0
                            Label {
                                anchors.centerIn: parent
                                text: "Нет операций. Добавьте доход или расход."
                                font.pixelSize: 14
                                color: "#888888"
                            }
                        }

                        delegate: Rectangle {
                            width: transactionsList.width
                            height: 56
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12
                                spacing: 16

                                Text {
                                    text: modelData.type === 1 ? "↑" : "↓"
                                    font.pixelSize: 18
                                    font.bold: true
                                    color: modelData.type === 1 ? "#4CAF50" : "#F44336"
                                    Layout.preferredWidth: 24
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 2

                                    Text {
                                        text: modelData.category + (modelData.description ? ": " + modelData.description : "")
                                        font.pixelSize: 14
                                        color: "#1E1E2E"
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }

                                    Text {
                                        text: modelData.createdAtFormatted
                                        font.pixelSize: 12
                                        color: "#888888"
                                    }
                                }

                                Text {
                                    text: financeViewModel.formatMoney(modelData.amountRubles)
                                    font.pixelSize: 14
                                    font.bold: true
                                    color: modelData.type === 1 ? "#4CAF50" : "#F44336"
                                }

                                Button {
                                    text: "✎"
                                    flat: true
                                    Layout.preferredWidth: 36
                                    Layout.preferredHeight: 36
                                    onClicked: {
                                        addIncomeDialog.isEdit = true
                                        addIncomeDialog.editId = modelData.id
                                        addIncomeDialog.editType = modelData.type
                                        addIncomeDialog.isIncome = modelData.type === 1
                                        addIncomeDialog.editAmount = modelData.amountRubles
                                        addIncomeDialog.editCategory = modelData.category
                                        addIncomeDialog.editDescription = modelData.description || ""
                                        addIncomeDialog.open()
                                    }
                                    background: Rectangle {
                                        color: parent.hovered ? "#E0E0E0" : "transparent"
                                        radius: 6
                                    }
                                }

                                Button {
                                    text: "✕"
                                    flat: true
                                    Layout.preferredWidth: 36
                                    Layout.preferredHeight: 36
                                    onClicked: {
                                        financeScreen.transactionToDelete = modelData.id
                                        confirmDeleteDialog.open()
                                    }
                                    background: Rectangle {
                                        color: parent.hovered ? "#FFCDD2" : "transparent"
                                        radius: 6
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    }

    FinanceTransactionDialog {
        id: addIncomeDialog
    }

    Dialog {
        id: confirmDeleteDialog
        modal: true
        title: "Удалить операцию?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            financeViewModel.deleteTransaction(financeScreen.transactionToDelete)
        }
    }

    Component.onCompleted: {
        financeViewModel.reload()
    }
}
