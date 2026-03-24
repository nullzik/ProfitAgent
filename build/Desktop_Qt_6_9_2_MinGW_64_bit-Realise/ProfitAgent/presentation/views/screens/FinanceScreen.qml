import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: financeScreen
    color: "#F5F5F5"

    property int currentTab: 0  // 0=all, 1=income, 2=expense
    property int transactionToDelete: 0
    property int typeFilter: 0  // 0=все, 1=продажи, 2=поставки, 3=зарплата, 4=премии, 5=штрафы, 6=прочее
    property var currentModel: []

    function matchesTypeFilter(tx) {
        if (!tx)
            return false;
        if (typeFilter === 0)
            return true;
        const cat = (tx.category || "");
        if (typeFilter === 1)
            return cat.startsWith("Продажи стол");
        if (typeFilter === 2)
            return cat.startsWith("Поставка:");
        if (typeFilter === 3)
            return cat.startsWith("Зарплата:");
        if (typeFilter === 4)
            return cat.startsWith("Премия:");
        if (typeFilter === 5)
            return cat.startsWith("Штраф:");
        // Прочее
        return !cat.startsWith("Продажи стол")
                && !cat.startsWith("Поставка:")
                && !cat.startsWith("Зарплата:")
                && !cat.startsWith("Премия:")
                && !cat.startsWith("Штраф:");
    }

    function baseListForCurrentTab() {
        if (tabBar.currentIndex === 0)
            return financeViewModel.transactions || [];
        if (tabBar.currentIndex === 1)
            return financeViewModel.incomeTransactions || [];
        return financeViewModel.expenseTransactions || [];
    }

    function rebuildCurrentModel() {
        const src = baseListForCurrentTab();
        const out = [];
        for (var i = 0; i < src.length; ++i) {
            const tx = src[i];
            if (matchesTypeFilter(tx))
                out.push(tx);
        }
        currentModel = out;
    }

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
            onCurrentIndexChanged: rebuildCurrentModel()
        }

        TabBar {
            id: detailsTabBar
            Layout.fillWidth: true

            TabButton {
                text: "Последние операции"
            }
            TabButton {
                text: "Агрегация по официантам"
            }
        }

        // Подвкладка: операции
        Rectangle {
            visible: detailsTabBar.currentIndex === 0
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

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Text {
                        text: "Тип операций:"
                        font.pixelSize: 13
                        color: "#666666"
                    }

                    ComboBox {
                        id: typeFilterCombo
                        model: ["Все", "Продажи", "Поставки", "Зарплата", "Премии", "Штрафы", "Прочее"]
                        onCurrentIndexChanged: {
                            financeScreen.typeFilter = currentIndex
                            rebuildCurrentModel()
                        }
                    }

                    Item { Layout.fillWidth: true }
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: transactionsList
                        width: parent.width - 20
                        clip: true
                        model: financeScreen.currentModel

                        footer: Item {
                            width: transactionsList.width
                            height: (financeScreen.currentModel && financeScreen.currentModel.length === 0) ? 200 : 0
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

        // Подвкладка: агрегация по официантам
        Rectangle {
            visible: detailsTabBar.currentIndex === 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#FFFFFF"
            radius: 12
            border.color: "#E0E0E0"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 8

                Text {
                    text: "Агрегация по официантам"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#1E1E2E"
                }

                Text {
                    visible: financeViewModel.waiterAggregates.length === 0
                    text: "Нет данных по официантам. Добавьте сотрудников с ролью \"Официант\" и закройте смены."
                    font.pixelSize: 13
                    color: "#888888"
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text { text: "Официант"; font.pixelSize: 13; font.bold: true; color: "#555555"; Layout.preferredWidth: 260 }
                    Text { text: "Часы"; font.pixelSize: 13; font.bold: true; color: "#555555"; Layout.preferredWidth: 80 }
                    Text { text: "Начислено, ₽"; font.pixelSize: 13; font.bold: true; color: "#555555"; Layout.preferredWidth: 140 }
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: financeViewModel.waiterAggregates
                    clip: true

                    delegate: Rectangle {
                        width: parent.width
                        height: 32
                        color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 4
                            spacing: 8

                            Text {
                                text: modelData.fullName
                                font.pixelSize: 13
                                color: "#1E1E2E"
                                elide: Text.ElideRight
                                Layout.preferredWidth: 260
                            }
                            Text {
                                text: Number(modelData.workedHours).toFixed(2)
                                font.pixelSize: 13
                                color: "#424242"
                                Layout.preferredWidth: 80
                            }
                            Text {
                                text: financeViewModel.formatMoney(modelData.salaryRubles)
                                font.pixelSize: 13
                                color: "#424242"
                                Layout.preferredWidth: 140
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
        rebuildCurrentModel()
    }

    Connections {
        target: financeViewModel
        function onTransactionsChanged() {
            rebuildCurrentModel()
            dashboardViewModel.reload()
        }
    }
}
