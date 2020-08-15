import QtQuick 2.0
import QtQuick.Controls 2.12

import "../js/global.js" as G
import "../js/util.js" as Util

Item {
    id: root
    property alias modelData: accountListView.model
    /*只读属性*/
    property int currentAccount: 0

    signal setCurrentAccount(int index)
    signal addAccount(string username, string password)
    signal addAccountFinished(string error)

    onAddAccountFinished: {
        Util.hideLoadingDialog()
        if ("" === error) {
            Util.closeAddAccountDialog()
        } else {
            Util.setAddAccountDialogErrorText(error)
        }
    }

    Button {
        id: btn
        text: qsTr("添加账号")
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        icon.source: "qrc:/icon/add.svg"
        palette {
            button: "transparent"
            buttonText: G.activeColor
        }
        onClicked: Util.showAddAccountDialog(function (username, password) {
            addAccount(username, password)
        })
    }

    ToolSeparator {
        id: toolSeparator
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: btn.bottom
        anchors.topMargin: 0
        orientation: Qt.Horizontal
    }

    ListView {
        id: accountListView
        anchors.rightMargin: 2
        anchors.bottomMargin: 2
        anchors.leftMargin: 2
        anchors.top: toolSeparator.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        clip: true
        delegate: AccountItem {
            id: accountItem
            onClicked: setCurrentAccount(index)
        }
        ScrollBar.vertical: ScrollBar {}
    }
}
