import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

import "Screens"

Window {
    id: window
    visible: true
    minimumWidth: 1000
    minimumHeight: 600
    width: 1000
    height: 600
    title: "Poker range trainer"

    Component {
        id: gridScreen
        GridScreen {}
    }
    Component {
        id: importScreen
        ImportScreen {}
    }

    Loader {
        id: pageLoader
        anchors.fill: parent

        property bool rangesParsed: false
        sourceComponent: rangesParsed ? gridScreen : importScreen
    }

    Connections {
        target: _rangeLoader
        function onParseEnded(success) {
           pageLoader.rangesParsed = success
        }

    }
}
