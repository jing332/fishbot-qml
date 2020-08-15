import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "./layout"
import "./js/global.js" as G
import "./servers"
import "./accounts"
import "./instances"
import "./settings"
import "./dialogs"
import "./components"

Rectangle {
    id: window
    color: G.bgColor

    property string activeTab: "服务器"

    //Tab侧边栏
    LeftSidebar {
        id: tabSidebar
        objectName: "tabSidebar"
        height: window.height

        onActiveChange: {
            activeTab = tab
            switch (tab) {
            case "服务器":
                stackLayout.currentIndex = 0
                break
            case "账户":
                stackLayout.currentIndex = 1
                break
            case "实例":
                stackLayout.currentIndex = 2
                break
            case "设置":
                stackLayout.currentIndex = 3
            }
        }
    }

    StackLayout {
        id: stackLayout
        objectName: "stackLayout"

        anchors.left: tabSidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.leftMargin: 4
        currentIndex: 0

        Servers {
            id: serversPage
            objectName: "serversPage"
        }

        Accounts {
            id: accountsPage
            objectName: "accountsPage"
        }

        Instances {
            id: instancesPage
            objectName: "instancesPage"
        }

        Settings {
            id: settingsPage
        }
    }

    ContentMenu {
        id: contentMenu
        Component.onCompleted: {
            G.appState.contentMenu = contentMenu
        }
    }
    LoadingDialog {
        id: loadingDlg
        Component.onCompleted: {
            G.appState.loadingDlg = loadingDlg
        }
    }

    Component.onCompleted: {
        G.appState.mainWindow = window
    }
}
