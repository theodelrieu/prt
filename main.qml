import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: window
    minimumWidth: 1000
    minimumHeight: 600
    width: 1000
    height: 600
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
