import QtQuick 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15

Item {
    implicitHeight: 640
    implicitWidth: 400
    FileDialog {
        id: equilabDialog
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        onAccepted: {
            console.log("chosen file:", equilabDialog.fileUrl)
            _rangeLoader.parseEquilab(equilabDialog.fileUrl)
        }
    }

    Connections {
        target: _rangeLoader
        function onParseStarted() {
            console.log("received parse started signal")
            equilabButton.enabled = false
            equilabButton.highlighted = true
        }
        function onParseEnded(success) {
            console.log("received parse ended signal", success)
            equilabButton.enabled = true
            equilabButton.highlighted = false
        }
    }

    Button {
        id: equilabButton
        anchors.centerIn: parent
        height: 100
        width: 200
        onClicked: equilabDialog.open()
        Text {
            text: "Import Equilab ranges"
            anchors.centerIn: parent
        }
    }
}
