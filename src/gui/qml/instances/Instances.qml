import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Item {
    id: root

    /*Call from C++*/
    function addTabPage(name, addr) {
        tabBar.addItem(tabButton.createObject(tabBar, {
                                                  "text": name,
                                                  "objectName": addr
                                              }))
        stackLayout.children.push(instance.createObject(stackLayout, {
                                                            "objectName": addr
                                                        }))
        return tabBar.count
    }

    function closeTabPage(addr) {
        for (var i = 0; i < tabBar.children.length; i++) {
            if (tabBar.children[i].objectName === addr) {
                tabBar.children[i].destroy()
                if (stackLayout.children[i].objectName === addr)
                    stackLayout.children[i].destroy()
            }
        }
    }

    Component {
        id: tabButton
        TabButton {}
    }

    Component {
        id: instance
        NewInstance {}
    }

    TabBar {
        id: tabBar
        height: 40
        anchors.top: root.top
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    StackLayout {
        id: stackLayout
        objectName: "stackLayout"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: tabBar.bottom
        anchors.topMargin: 16
        currentIndex: tabBar.currentIndex
    }
}
