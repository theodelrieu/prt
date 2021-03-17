import QtQuick 2.15
import Qt.labs.platform 1.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: root
    implicitHeight: 640
    implicitWidth: 400

    property bool __parsing: false
    FileDialog {
        id: equilabDialog
        title: "Select Equilab range file"
        defaultSuffix: "hr"
        nameFilters: ["Equilab range files (*.hr)"]
        onAccepted: {
            equilabButton.highlighted = true
            _rangeLoader.parseEquilab(equilabDialog.file)
        }
    }
    FolderDialog {
        id: pioDialog
        title: "Select PioSOLVER ranges folder"
        onAccepted: {
            pioButton.highlighted = true
            _rangeLoader.parsePio(pioDialog.folder)
        }
    }

    Connections {
        target: _rangeLoader
        function onParseStarted() {
            root.__parsing = true;
        }
        function onParseEnded(success) {
            console.log("onParseEnded called", success)
            root.__parsing = false;
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Button {
            id: equilabButton
            enabled: !root.__parsing
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
            enabled: !root.__parsing
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
