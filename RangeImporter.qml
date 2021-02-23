import QtQuick 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15

Item {
    implicitHeight: 640
    implicitWidth: 400
    height: window.height
    width: window.width
    FileDialog {
        id: equilabDialog
        folder: shortcuts.documents
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        onAccepted: {
            _rangeLoader.parseEquilab(equilabDialog.fileUrl)
        }
    }

    Connections {
        target: _rangeLoader
        function onParseStarted() {
            equilabButton.enabled = false
            equilabButton.highlighted = true
        }
        function onParseEnded(success) {
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
