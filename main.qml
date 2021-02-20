import QtQuick 2.5
import QtQuick.Window 2.5
import QtQuick.Controls 1.4
import Qt.labs.platform 1.1

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Poker range trainer"

    Connections {
        target: _rangeLoader
        function onParseStarted() { console.log("received parse started signal") }
        function onParseEnded(success) { console.log("received parse ended signal", success); }
    }

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

    FileDialog {
        id: equilabDialog
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        options: FileDialog.ReadOnly
        onAccepted: {
            console.log("chosen file:", equilabDialog.file)
            _rangeLoader.parseEquilab(equilabDialog.file)
        }
    }


    Button {
        anchors.centerIn: parent
        height: parent.height / 4
        width: parent.width / 4
        onClicked: equilabDialog.open()
        Text {
            text: "Import Equilab ranges"
            anchors.centerIn: parent
        }
    }
}
