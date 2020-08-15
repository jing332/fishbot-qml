import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    width: parent.width
    height: 35
    color: "transparent"
    radius: 4
    property alias icon: iconImg.source
    property alias tabText: tabBtn.text
    property alias iconColorOverlay: colorOverlay.visible
    property bool active
    property string activeColor
    property string inactiveColor
    signal activeChange(string tab)

    Rectangle {
        id: rectLine
        width: 3
        height: root.height * 0.5
        anchors.verticalCenter: parent.verticalCenter
        color: active ? activeColor : "transparent"
    }
    PropertyAnimation {
        id: animation
        target: rectLine
        property: "height"
        from: 0
        to: root.height * 0.5
        duration: 130
        onStarted: rectLine.height = 0
    }

    Image {
        id: iconImg
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 8
        visible: Image.Null === iconImg.status ? false : true
    }
    ColorOverlay {
        id: colorOverlay
        anchors.fill: iconImg
        source: iconImg
        color: tabBtn.color
        visible: iconImg.visible
    }

    Text {
        id: tabBtn
        height: root.height
        font.pointSize: 12
        font.bold: active ? true : false
        color: {
            if (active)
                return activeColor
            if (ma.containsMouse)
                return Qt.lighter(activeColor, 1.2)
            return inactiveColor
        }
        anchors.left: iconImg.right
        anchors.right: parent.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter

        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 4
        horizontalAlignment: Text.AlignLeft
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            if (!active) {
                activeChange(tabText)
                animation.start()
            }
        }
        cursorShape: active ? Qt.ArrowCursor : Qt.PointingHandCursor
    }
}
