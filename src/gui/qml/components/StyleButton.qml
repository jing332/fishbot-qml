import QtQuick 2.0
import QtQuick.Controls 2.12

import "../js/global.js" as G

Button {
    id: root
    palette {
        buttonText: root.enabled ? G.activeColor : Qt.darker(G.activeColor, 1.4)
    }
    background: Rectangle {
        radius: 4
        color: {
            if (!root.enabled) {
                return Qt.lighter(G.bgColor, 1.4)
            } else if (root.pressed) {
                return Qt.lighter(G.bgColor, 1.3)
            } else {
                return Qt.lighter(G.bgColor, 1.2)
            }
        }
    }
}
