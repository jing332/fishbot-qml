import QtQuick 2.0
import QtQuick.Controls 2.12
import "../js/global.js" as G

Menu {
    id: root
    Component {
        id: menuComp
        MenuItem {
            property var m
            text: m.name
            onTriggered: {
                m.cb(m.name)
            }
        }
    }
    function show(menus) {
        while (root.count > 0)
            root.removeItem(0)
        menus.forEach(function (item) {
            var ins = menuComp.createObject(null, {
                                                "m": item
                                            })
            root.addItem(ins)
        })
        root.popup()
    }
}
