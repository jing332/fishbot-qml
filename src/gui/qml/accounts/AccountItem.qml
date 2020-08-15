import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../js/global.js" as G

Rectangle {
    id: root
    width: parent ? parent.width : 0
    height: 50
    color: "transparent"
    signal clicked

    MouseArea {
        id: ma
        height: 50
        anchors.fill: root
        hoverEnabled: true
        onEntered: root.color = Qt.lighter(G.bgColor, 1.2)
        onExited: root.color = "transparent"
        onClicked: root.clicked()
    }

    Image {
        id: selectImg
        width: 32
        height: 32
        visible: isSelected ? true : false
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        fillMode: Image.Pad
        source: "qrc:/icon/selected.svg"
        anchors.leftMargin: 2
        sourceSize.width: 18
        sourceSize.height: 18
    }
    ColorOverlay {
        source: selectImg
        color: G.activeColor
        anchors.fill: selectImg
        visible: isSelected ? true : false
    }

    Text {
        id: usernameText
        height: 20
        anchors.right: parent.right
        anchors.left: selectImg.right
        anchors.leftMargin: 4
        color: G.activeColor
        font.pixelSize: 16
        anchors.verticalCenterOffset: -8
        text: 2 === type ? displayName : displayName + " - " + username
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: typeText
        width: 200
        text: {
            switch (type) {
            case 0:
                return "正版登陆"
            case 1:
                return "外置登陆"
            case 2:
                return "离线模式"
            }
        }
        anchors.top: usernameText.bottom
        anchors.left: selectImg.right
        anchors.topMargin: 2
        font.pixelSize: 12
        anchors.leftMargin: 4
        color: "darkgray"
    }
}
