import QtQuick 2.0
import QtQuick.Controls 2.12
import "../js/global.js" as G

TextField {
    id: root
    color: G.activeColor
    background: Rectangle {
        radius: 2
        color: Qt.lighter(G.bgColor, 1.2)
        border.width: parent.activeFocus ? 2 : 0
    }
    selectByMouse: true
}
