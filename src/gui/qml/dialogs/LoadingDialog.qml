import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../js/app.js" as App

Dialog {
    id: root
    width: 100
    height: 100
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose
    anchors.centerIn: Overlay.overlay
    background: Rectangle {
        color: "transparent"
    }

    BusyIndicator {
        id: busyIndicator
        wheelEnabled: true
        anchors.fill: parent
        palette.dark: "red"
    }
    //    AnimatedImage {
    //        anchors.fill: parent
    //        source: "qrc:/background/loading.gif"
    //    }
}
