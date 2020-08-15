import QtQuick 2.0
import "../components"
import QtQuick.Controls 2.12
import com.jing.fishbot 1.0

Item {
    id: root
    signal sendMessage(string msg)
    property alias chatsModel: listView.model

    ListView {
        id: listView
        spacing: 2
        anchors.bottom: row.top
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 2

        delegate: Item {
            width: parent ? parent.width : 0
            height: 16

            ChatText {
                anchors.fill: parent
                text: formatedText
            }
        }
        onCountChanged: {
            listView.positionViewAtEnd()
        }

        ScrollBar.vertical: ScrollBar {}
    }

    Item {
        id: row
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4

        StyleTextField {
            id: msgTextField
            anchors.right: sendBtn.left
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                    sendBtn.clicked()
                }
            }
        }

        StyleButton {
            id: sendBtn
            width: 80
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 0
            text: "发送"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onClicked: {
                root.sendMessage(msgTextField.text)
                msgTextField.clear()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:160;anchors_width:110;anchors_x:220;anchors_y:137}
}
##^##*/

