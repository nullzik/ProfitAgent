import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: menuScreen
    color: "#F5F5F5"

    property var selectedDish: null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Text {
                text: "Меню"
                font.pixelSize: 28
                font.bold: true
                color: "#1E1E2E"
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "+ Добавить блюдо"
                onClicked: createDishDialog.open()
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

        // Отображение последней ошибки
        Text {
            visible: menuViewModel.lastError.length > 0
            text: menuViewModel.lastError
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

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Text {
                    text: "Список блюд"
                    font.pixelSize: 18
                    font.bold: true
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: dishesList
                        width: parent.width
                        height: parent.height
                        clip: true
                        model: menuViewModel.dishes

                        delegate: Rectangle {
                            width: ListView.view.width
                            height: 80
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"
                            radius: 6

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12

                                MouseArea {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        selectedDish = modelData
                                        dishDialog.open()
                                    }

                                    ColumnLayout {
                                        anchors.fill: parent
                                        spacing: 4

                                        Text {
                                            text: modelData.name
                                            font.pixelSize: 16
                                            font.bold: true
                                            color: "#1E1E2E"
                                        }

                                        RowLayout {
                                            spacing: 16

                                            Text {
                                                text: "Цена продажи: " + modelData.salePrice.toFixed(2) + " ₽"
                                                font.pixelSize: 13
                                                color: "#4CAF50"
                                            }

                                            Text {
                                                text: "Себестоимость: " + modelData.costPrice.toFixed(2) + " ₽"
                                                font.pixelSize: 13
                                                color: "#666666"
                                            }

                                            Text {
                                                text: "Прибыль: " + (modelData.salePrice - modelData.costPrice).toFixed(2) + " ₽"
                                                font.pixelSize: 13
                                                color: "#2196F3"
                                            }
                                        }

                                        Text {
                                            text: modelData.isAvailable ? "✓ Доступно" : "✗ Недоступно"
                                            font.pixelSize: 12
                                            color: modelData.isAvailable ? "#4CAF50" : "#F44336"
                                        }
                                    }
                                }

                                Button {
                                    text: "Удалить"
                                    onClicked: {
                                        menuViewModel.deleteDish(modelData.id)
                                    }
                                    background: Rectangle {
                                        color: parent.hovered ? "#F44336" : "#E53935"
                                        radius: 6
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: "#FFFFFF"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: 12
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Диалог создания/редактирования блюда
    Dialog {
        id: createDishDialog
        modal: true
        title: selectedDish ? "Редактировать блюдо" : "Добавить новое блюдо"
        width: 600
        height: 500

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "ID блюда"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    TextField {
                        id: dishIdField
                        Layout.fillWidth: true
                        height: 48
                        placeholderText: "Например: pasta_carbonara"
                        enabled: !selectedDish
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
                        text: "Название блюда"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    TextField {
                        id: dishNameField
                        Layout.fillWidth: true
                        height: 48
                        placeholderText: "Например: Паста Карбонара"
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
                        text: "Цена продажи (₽)"
                        font.pixelSize: 14
                        color: "#666666"
                    }

                    TextField {
                        id: salePriceField
                        Layout.fillWidth: true
                        height: 48
                        placeholderText: "Например: 450.00"
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FFFFFF"
                        }
                    }
                }

                CheckBox {
                    id: isAvailableCheckBox
                    text: "Доступно для заказа"
                    checked: true
                }

                Item {
                    Layout.fillHeight: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Button {
                        Layout.fillWidth: true
                        text: "Отмена"
                        onClicked: {
                            createDishDialog.close()
                            selectedDish = null
                            dishIdField.text = ""
                            dishNameField.text = ""
                            salePriceField.text = ""
                            isAvailableCheckBox.checked = true
                        }
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
                        Layout.fillWidth: true
                        text: selectedDish ? "Сохранить" : "Создать"
                        onClicked: {
                            const id = dishIdField.text.trim()
                            const name = dishNameField.text.trim()
                            const price = Number(salePriceField.text)

                            if (id.length === 0 || name.length === 0 || price <= 0) {
                                return
                            }

                            if (selectedDish) {
                                menuViewModel.updateDish(id, name, price, isAvailableCheckBox.checked)
                            } else {
                                menuViewModel.createDish(id, name, price)
                            }

                            createDishDialog.close()
                            selectedDish = null
                            dishIdField.text = ""
                            dishNameField.text = ""
                            salePriceField.text = ""
                            isAvailableCheckBox.checked = true
                        }
                        background: Rectangle {
                            color: parent.hovered ? "#4CAF50" : "#5CBF60"
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

    // Диалог рецепта блюда
    Dialog {
        id: dishDialog
        modal: true
        title: selectedDish ? selectedDish.name : "Рецепт блюда"
        width: 700
        height: 600

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                Text {
                    text: "Рецепт: " + (selectedDish ? selectedDish.name : "")
                    font.pixelSize: 18
                    font.bold: true
                    Layout.fillWidth: true
                }

                Text {
                    text: "Ингредиенты:"
                    font.pixelSize: 14
                    font.bold: true
                    Layout.fillWidth: true
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: recipeList
                        width: parent.width
                        model: selectedDish ? menuViewModel.getRecipe(selectedDish.id) : []

                        delegate: Rectangle {
                            width: ListView.view.width
                            height: 50
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12

                                Text {
                                    text: {
                                        // Find product name from warehouse
                                        for (var i = 0; i < warehouseViewModel.products.length; i++) {
                                            if (warehouseViewModel.products[i].id === modelData.productId) {
                                                return warehouseViewModel.products[i].name
                                            }
                                        }
                                        return modelData.productId
                                    }
                                    font.pixelSize: 14
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: modelData.quantity + " г"
                                    font.pixelSize: 13
                                    color: "#666666"
                                }
                            }
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Редактировать рецепт"
                    onClicked: {
                        recipeEditDialog.open()
                    }
                    background: Rectangle {
                        color: parent.hovered ? "#2196F3" : "#1976D2"
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
                    Layout.fillWidth: true
                    text: "Редактировать блюдо"
                    onClicked: {
                        dishDialog.close()
                        dishIdField.text = selectedDish.id
                        dishNameField.text = selectedDish.name
                        salePriceField.text = selectedDish.salePrice
                        isAvailableCheckBox.checked = selectedDish.isAvailable
                        createDishDialog.open()
                    }
                    background: Rectangle {
                        color: parent.hovered ? "#4CAF50" : "#5CBF60"
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
                    Layout.fillWidth: true
                    text: "Закрыть"
                    onClicked: dishDialog.close()
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
            }
        }
    }

    // Диалог редактирования рецепта
    Dialog {
        id: recipeEditDialog
        modal: true
        title: "Редактировать рецепт"
        width: 600
        height: 500

        contentItem: Rectangle {
            color: "#FFFFFF"
            radius: 12

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                Text {
                    text: "Добавить ингредиент:"
                    font.pixelSize: 16
                    font.bold: true
                    Layout.fillWidth: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    ComboBox {
                        id: productComboBox
                        Layout.fillWidth: true
                        height: 48
                        model: warehouseViewModel.products
                        textRole: "name"
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FFFFFF"
                        }
                    }

                    TextField {
                        id: quantityField
                        Layout.preferredWidth: 120
                        height: 48
                        placeholderText: "Кол-во"
                        background: Rectangle {
                            radius: 8
                            border.color: "#E0E0E0"
                            border.width: 1
                            color: "#FFFFFF"
                        }
                    }

                    Button {
                        text: "Добавить"
                        onClicked: {
                            if (productComboBox.currentIndex >= 0 && quantityField.text.length > 0) {
                                const product = warehouseViewModel.products[productComboBox.currentIndex]
                                const quantity = Number(quantityField.text)
                                
                                var ingredients = menuViewModel.getRecipe(selectedDish.id)
                                var found = false
                                for (var i = 0; i < ingredients.length; i++) {
                                    if (ingredients[i].productId === product.id) {
                                        ingredients[i].quantity = quantity
                                        found = true
                                        break
                                    }
                                }
                                if (!found) {
                                    ingredients.push({
                                        productId: product.id,
                                        quantity: quantity
                                    })
                                }
                                
                                menuViewModel.setRecipe(selectedDish.id, ingredients)
                                quantityField.text = ""
                            }
                        }
                        background: Rectangle {
                            color: parent.hovered ? "#4CAF50" : "#5CBF60"
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

                Text {
                    text: "Текущие ингредиенты:"
                    font.pixelSize: 14
                    font.bold: true
                    Layout.fillWidth: true
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: currentRecipeList
                        width: parent.width
                        model: selectedDish ? menuViewModel.getRecipe(selectedDish.id) : []

                        delegate: Rectangle {
                            width: ListView.view.width
                            height: 50
                            color: index % 2 === 0 ? "#FAFAFA" : "#FFFFFF"

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 12

                                Text {
                                    text: {
                                        for (var i = 0; i < warehouseViewModel.products.length; i++) {
                                            if (warehouseViewModel.products[i].id === modelData.productId) {
                                                return warehouseViewModel.products[i].name
                                            }
                                        }
                                        return modelData.productId
                                    }
                                    font.pixelSize: 14
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: modelData.quantity + " г"
                                    font.pixelSize: 13
                                    color: "#666666"
                                }

                                Button {
                                    text: "Удалить"
                                    onClicked: {
                                        var ingredients = menuViewModel.getRecipe(selectedDish.id)
                                        ingredients.splice(index, 1)
                                        menuViewModel.setRecipe(selectedDish.id, ingredients)
                                    }
                                    background: Rectangle {
                                        color: parent.hovered ? "#F44336" : "#E53935"
                                        radius: 6
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: "#FFFFFF"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.pixelSize: 11
                                    }
                                }
                            }
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Закрыть"
                    onClicked: recipeEditDialog.close()
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
            }
        }
    }
}

