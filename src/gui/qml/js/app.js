.pragma library
.import "./global.js" as G

G.appState = (function () {
    var comp = Qt.createComponent("qrc:/qml/js/appState.qml")
    return comp.createObject()
})()
