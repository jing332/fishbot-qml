import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root

    signal clicked
    signal pressed
    signal released

    property string text
    property string imageSource
    width: 60
    height: 30
    Image {
        id: img
        width: btn.height
        height: btn.height
        anchors.right: textBtn.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        source: imageSource
    }

    Text {
        id: textBtn
        text: root.text
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: img.right
        anchors.leftMargin: 0
    }

    MouseArea {
        id: ma
        anchors.fill: root
        onClicked: root.clicked()
        onPressed: root.pressed()
        onReleased: root.released()
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:0}
}
##^##*/

