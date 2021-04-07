import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.12

import ".."
import "../Enums"

ColumnLayout {
    Item {
        // spacer item, otherwise aligning to the center will not work
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    ListView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: _quizSettings
        delegate: Rectangle {
            height: 40
            width: ListView.view.width
            color: "pink"
            CheckBox {
                anchors.centerIn: parent
                checked: model.value
                text: model.name
                onClicked: model.value = (checkState === Qt.Checked)
            }
        }
    }

    Button {
        id: quizButton
        Layout.alignment: Qt.AlignBaseline | Qt.AlignHCenter
        Layout.preferredWidth: quizText.implicitWidth * 1.5
        Layout.preferredHeight: quizText.implicitHeight * 1.5

        Text {
            id: quizText
            anchors.centerIn: parent
            text: GlobalState.mode === Mode.View ? "Start quiz" : "Stop quiz"
        }

        onClicked: function () {
            if (GlobalState.mode === Mode.View) {
                _quizer.start()
            }
            else {
                _quizer.stop()
                GlobalState.mode = Mode.View
            }
        }
    }
}
