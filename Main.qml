import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    width: 1400
    height: 900
    visible: true
    title: "ProfitAgent"

    Loader {
        id: screenLoader
        anchors.fill: parent
        
        function updateSource() {
            if (!appStateViewModel.isAuthenticated) {
                sourceComponent = loginScreenComponent
            } else {
                switch (appStateViewModel.currentRole) {
                case AppStateViewModel.Waiter:
                    sourceComponent = waiterScreenComponent
                    break
                case AppStateViewModel.Chef:
                    sourceComponent = chefScreenComponent
                    break
                case AppStateViewModel.Manager:
                    sourceComponent = managerScreenComponent
                    break
                default:
                    sourceComponent = loginScreenComponent
                }
            }
        }

        Component.onCompleted: updateSource()
    }

    Connections {
        target: appStateViewModel
        function onIsAuthenticatedChanged() {
            screenLoader.updateSource()
        }
        function onCurrentRoleChanged() {
            screenLoader.updateSource()
        }
    }

    Component {
        id: loginScreenComponent
        LoginScreen {}
    }

    Component {
        id: waiterScreenComponent
        WaiterScreen {}
    }

    Component {
        id: chefScreenComponent
        ChefScreen {}
    }

    Component {
        id: managerScreenComponent
        ManagerScreen {}
    }

    // Обработка успешного входа
    Connections {
        target: authViewModel
        function onLoginSuccess(role) {
            appStateViewModel.loginAs(role)
        }
    }
}
