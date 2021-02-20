import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Poker range trainer"

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "RangeImporter.qml"
    }

    Connections {
        target: _rangeLoader
        function onParseEnded(success) {
            if (success)
                pageLoader.source = "MainScreen.qml"
        }

    }
}
