import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components" as Comps
import "../js/global.js" as G

Dialog {
    id: root
    width: 350
    height: 250
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: Overlay.overlay

    signal finished(string name, string host)
    //    property int index: -1
    property alias name: nameTextField.text
    property alias addr: addrTextField.text

    background: Rectangle {
        id: rect
        anchors.fill: parent
        radius: 8
        border.width: 2
        border.color: G.activeColor
        color: Qt.lighter(G.bgColor, 1.5)
    }
    Label {
        id: titleLabel
        text: "添加服务器"
        color: G.activeColor
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: true
        font.pointSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignLeft
    }

    GridLayout {
        id: gridLayout
        height: 100
        anchors.verticalCenter: parent.verticalCenter
        rows: 2
        anchors.right: parent.right
        anchors.left: parent.left
        columns: 2
        Label {
            id: label
            Layout.leftMargin: 20
            color: G.activeColor
            text: "服务器名称"
        }
        Comps.StyleTextField {
            id: nameTextField
            Layout.rightMargin: 20
            Layout.fillWidth: true
            placeholderText: "Minecraft Server"
            onTextChanged: parent.checkText()
        }
        Label {
            id: label1
            text: "服务器地址"
            color: G.activeColor
            Layout.leftMargin: 20
        }
        Comps.StyleTextField {
            id: addrTextField
            Layout.rightMargin: 20
            Layout.fillWidth: true
            placeholderText: qsTr("localhost")
            onTextChanged: parent.checkText()
        }

        function checkText() {
            if ("" === nameTextField || "" === addrTextField.text) {
                okBtn.enabled = false
            } else {
                okBtn.enabled = true
            }
        }
    }
    RowLayout {
        id: rowLayout
        height: 35
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        Comps.StyleButton {
            id: okBtn
            text: "完成"
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            onClicked: {
                close()
                finished(nameTextField.text, addrTextField.text)
            }
        }
        Comps.StyleButton {
            id: cancelBtn
            text: "取消"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onClicked: close()
        }
    }
}

/*##^##
Designer {
    D{i:9;anchors_height:100;anchors_width:100}D{i:3;anchors_height:100;anchors_width:100;anchors_x:120;anchors_y:139}
}
##^##*/

