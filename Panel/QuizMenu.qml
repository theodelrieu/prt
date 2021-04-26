import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.12

import ".."
import "../Enums"
import "../Components"

ColumnLayout {
    Item {
        // spacer item, otherwise aligning to the center will not work
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    // Text {
    //     text: "Do not quiz hands which are 100% in the range"
    //     Layout.fillWidth: true
    //     wrapMode: Text.Wrap
    //     // TODO move this object + listview in a QuizSettings object later on
    //     visible: GlobalState.mode === Mode.View
    // }

    ListView {
        interactive: false
        visible: GlobalState.mode === Mode.View
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: _quizSetting
        delegate: Rectangle {
            height: 20
            width: ListView.view.width
            CustomCheckBox {
                anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
                checked: model.value
                text: model.name
                onCheckedChanged: model.value = (checkState === Qt.Checked)
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
