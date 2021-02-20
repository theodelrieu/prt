import QtQuick 2.15
import QtQuick.Controls 1.4

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

    /*

    TreeView {
        id: treeView
        TableViewColumn {
            title: "Title"
            role: "display"
            width: 200
        }
        model: _rangeTreeModel
        itemDelegate: Item {
            Text {
                anchors.verticalCenter: parent.VerticalCenter
                text: styleData.value
            }
        }
    }
    */
}
