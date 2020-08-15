import QtQuick 2.0
import QtQuick.Controls 2.12
import com.jing.fishbot 1.0

import "../js/global.js" as G
import "../js/util.js" as Util

Rectangle {
    id: root
    height: 70
    enabled: true
    transformOrigin: Item.Center

    signal editServer(int index, string name, string addr)

    Base64Image {
        id: faviconImg
        width: 64
        height: 64
        anchors.verticalCenter: parent.verticalCenter
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 2
        base64: favicon
        source: "qrc:/background/unknown_server.png"
    }
    Text {
        id: nameText
        text: name
        anchors.left: faviconImg.right
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 4
        color: G.activeColor
        font.bold: true
        font.pixelSize: 16
    }

    ChatText {
        id: motdText
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: nameText.bottom
        anchors.topMargin: 4
        anchors.left: faviconImg.right
        anchors.leftMargin: 8
        text: motd
    }

    Text {
        id: delayText
        width: 35
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 4
        font.pixelSize: 12
        text: delay
        horizontalAlignment: Text.AlignRight
        color: G.activeColor
    }

    Text {
        id: onlinePlayersText
        anchors.right: delayText.left
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 4
        font.pixelSize: 12
        text: onlinePlayers
        color: G.activeColor
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: Util.showContentMenu(menus)

        property var menus: [{
                "name": "刷新",
                "cb": function () {
                    refreshServerStatus(index)
                }
            }, {
                "name": "编辑",
                "cb": function () {
                    Util.showEditServerDialog(name, addr,
                                              function (name, addr) {
                                                  editServer(index, name, addr)
                                              })
                }
            }, {
                "name": "移除",
                "cb": function () {
                    modelData.remove(index)
                }
            }]
    }
}
