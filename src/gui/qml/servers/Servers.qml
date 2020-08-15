import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../js/util.js" as Util
import "../components"

Rectangle {
    id: root
    color: "transparent"
    property alias modelData: serverListView.model

    signal serverDoubleClicked(int index)
    signal refreshAllServerStatus
    signal refreshServerStatus(int index)
    signal addServer(string name, string addr)
    signal editServer(int index, string name, string addr)

    ListView {
        id: serverListView
        anchors.bottom: row.top
        anchors.bottomMargin: 4
        spacing: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        clip: true

        delegate: ServerItem {
            id: serverItem
            color: "transparent"
            width: parent ? parent.width : 0
            onEditServer: root.editServer(index, name, addr)
            MouseArea {
                anchors.fill: parent
                onDoubleClicked: root.serverDoubleClicked(index)
            }
        }
        ScrollBar.vertical: ScrollBar {}
    }

    RowLayout {
        id: row
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        spacing: 10

        StyleButton {
            id: refreshBtn
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pointSize: 12
            text: "刷新"
            onClicked: root.refreshAllServerStatus()
        }

        StyleButton {
            id: addBtn
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            font.pointSize: 12
            text: "添加"
            onClicked: Util.showAddServerDialog(function (name, addr) {
                addServer(name, addr)
            })
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_width:640;anchors_x:8;anchors_y:8}
D{i:4;anchors_height:40}
}
##^##*/

