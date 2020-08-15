import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components" as Comps
import "../js/util.js" as Util
import "../js/global.js" as G

Dialog {
    id: root
    width: 350
    height: 250
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: Overlay.overlay
    background: Rectangle {
        id: rect
        anchors.fill: parent
        color: G.bgColor
    }

    property alias errorText: error.text
    signal finished(string username, string password)

    Button {
        id: closeBtn
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        width: 32
        height: 32
        icon.source: "qrc:/icon/close.svg"
        icon.color: G.activeColor
        background: Rectangle {
            id: bgRect
            radius: 50
            color: closeBtn.activeFocus ? Qt.lighter(G.bgColor,
                                                     1.2) : "transparent"
        }
        onClicked: root.close()
    }

    Item {
        id: content
        width: 350
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        Label {
            id: titleLabel
            text: "添加账户"
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
            height: 130
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.left: parent.left
            columns: 2
            rows: 4
            Label {
                id: typeLabel
                Layout.leftMargin: 20
                color: G.activeColor
                text: "登陆方式"
            }
            ComboBox {
                id: typeCmb
                height: 20
                Layout.maximumHeight: 25
                Layout.rightMargin: 20
                Layout.fillWidth: true
                model: ["正版登陆", "外置登陆", "离线模式"]
                onCurrentIndexChanged: {
                    switch (currentIndex) {
                    case 0:
                        authServerLabel.visible = false
                        authServerCmb.visible = false
                        pwdLabel.visible = true
                        pwdTextField.visible = true
                        usernameLabel.text = "邮箱"
                        userNameTextField.placeholderText = "Email"
                        okBtn.text = "登陆"
                        break
                    case 1:
                        authServerLabel.visible = true
                        authServerCmb.visible = true
                        pwdLabel.visible = true
                        pwdTextField.visible = true
                        usernameLabel.text = "邮箱"
                        userNameTextField.placeholderText = "Email"
                        okBtn.text = "登陆"
                        break
                    case 2:
                        authServerLabel.visible = false
                        authServerCmb.visible = false
                        pwdLabel.visible = false
                        pwdTextField.visible = false
                        usernameLabel.text = "离线用户名"
                        userNameTextField.placeholderText = "Steve"
                        okBtn.text = "添加"
                        break
                    }
                }
            }

            Label {
                id: authServerLabel
                Layout.leftMargin: 20
                color: G.activeColor
                text: "认证服务器"
            }
            ComboBox {
                id: authServerCmb
                height: 20
                Layout.maximumHeight: 25
                Layout.rightMargin: 20
                Layout.fillWidth: true
                model: authServersData
                //                delegate: Rectangle {
                //                    id: authServerItem
                //                    width: authServerCmb.width
                //                    height: 20
                //                    //                    Text {
                //                    //                        id: nameText
                //                    //                        text: qsTr("text")
                //                    //                    }
                //                }
            }

            Label {
                id: usernameLabel
                Layout.leftMargin: 20
                color: G.activeColor
                text: "邮箱"
            }
            Comps.StyleTextField {
                id: userNameTextField
                Layout.rightMargin: 20
                Layout.fillWidth: true
                placeholderText: "Email"
                onTextChanged: root.checkText()
            }
            Label {
                id: pwdLabel
                text: "密码"
                color: G.activeColor
                Layout.leftMargin: 20
            }
            Comps.StyleTextField {

                id: pwdTextField
                Layout.rightMargin: 20
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: "Password"
                onTextChanged: root.checkText()
            }
        }
        Text {
            id: error
            height: 20
            color: "red"
            anchors.top: gridLayout.bottom
            anchors.topMargin: 4
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
        }

        Comps.StyleButton {
            id: okBtn
            width: 300
            height: 40
            enabled: false
            anchors.top: error.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 2
            text: "登陆"
            onClicked: finished(userNameTextField.text, pwdTextField.text)
        }

        Component.onCompleted: {
            checkText()
        }
    }

    function checkText() {
        if (2 !== typeCmb.currentIndex) {
            if ("" === userNameTextField.text || "" === pwdTextField.text) {
                okBtn.enabled = false
            } else {
                okBtn.enabled = true
            }
        } else {
            /*离线模式*/
            if ("" === userNameTextField.text) {
                okBtn.enabled = false
            } else {
                okBtn.enabled = true
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}D{i:8;annotation:"1 //;;//  //;;//  //;;// <!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Titillium Web'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html> //;;// 1594947996";customId:""}
}
##^##*/

