import QtQuick 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    implicitHeight: 640
    implicitWidth: 400

    FileDialog {
        id: equilabDialog
        folder: shortcuts.home
        title: "Select Equilab range file"
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        onAccepted: {
            _rangeLoader.parseEquilab(equilabDialog.fileUrl)
        }
    }
    FileDialog {
        id: pioDialog
        title: "Select PioSOLVER ranges folder"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            _rangeLoader.parsePio(pioDialog.fileUrl)
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

    ColumnLayout {
        anchors.fill: parent
        Button {
            id: equilabButton
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.3

            onClicked: equilabDialog.open()
            Text {
                id: txt
                text: "Import Equilab ranges"
                anchors.centerIn: parent
            }
        }
        Button {
            id: pioButton
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.3
            onClicked: pioDialog.open()
            Text {
                text: "Import PioSOLVER ranges"
                anchors.centerIn: parent
            }
        }
    }
}
