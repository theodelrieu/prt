import QtQuick 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15

Item {
    implicitHeight: 640
    implicitWidth: 400

    FileDialog {
        id: equilabDialog
        folder: shortcuts.documents
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        onAccepted: {
            _rangeLoader.parseEquilab(equilabDialog.fileUrl)
        }
    }
    FileDialog {
        id: pioDialog
        folder: shortcuts.documents
        defaultSuffix: "txt"
        nameFilters: ["PioSOLVER range files (*.txt)"]
        onAccepted: {
            _rangeLoader.parsePio(pioDialog.fileUrls)
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

    ColumnView {
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
    Button {
        id: pioButton
        anchors.centerIn: parent
        height: 100
        width: 200
        onClicked: pioDialog.open()
        Text {
            text: "Import PioSOLVER ranges"
            anchors.centerIn: parent
        }
    }
    }
}
