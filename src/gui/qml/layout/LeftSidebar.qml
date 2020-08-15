import QtQuick 2.12

import "../js/global.js" as G

Rectangle {
    id: root
    width: 100
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.top: parent.top

    color: "#2a2a2a"
    property int btnWidth: 30
    property color activeColor: G.activeColor
    property color inactiveColor: "darkgray"
    property string activeTab: "服务器"
    signal activeChange(string tab)
    onActiveChange: {
        activeTab = tab
    }

    Column {
        id: columnTab
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 4
        spacing: 4

        Repeater {
            id: repeater
            model: ListModel {
                ListElement {
                    text: "服务器"
                    icon: "qrc:/background/unknown_server.png"
                    iconColorOverlay: false
                }
                ListElement {
                    text: "账户"
                    icon: "qrc:/background/avatar_steve.png"
                    iconColorOverlay: false
                }
            }

            TabItem {
                active: text === activeTab
                activeColor: root.activeColor
                inactiveColor: root.inactiveColor
                onActiveChange: root.activeChange(tab)
                tabText: text
                icon: undefined === model.icon ? "" : model.icon
                iconColorOverlay: model.iconColorOverlay
            }
        }
    }

    TabItem {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        active: "设置" === activeTab
        activeColor: root.activeColor
        inactiveColor: root.inactiveColor
        onActiveChange: root.activeChange(tab)
        tabText: "设置"
        icon: "qrc:/icon/options.svg"
    }

    Column {
        id: instanceColumn
        width: root.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: columnTab.bottom
        anchors.topMargin: 20
        spacing: 4

        Repeater {
            id: instanceRepeater
            model: ListModel {
                ListElement {
                    text: "实例"
                    icon: "qrc:/icon/instance.svg"
                    iconColorOverlay: true
                }
            }

            TabItem {
                active: text === activeTab
                activeColor: root.activeColor
                inactiveColor: root.inactiveColor
                onActiveChange: root.activeChange(tab)
                tabText: text
                icon: model.icon
                iconColorOverlay: model.iconColorOverlay
            }
        }
    }
}

/*##^##
Designer {
    D{i:8;anchors_y:40}
}
##^##*/

