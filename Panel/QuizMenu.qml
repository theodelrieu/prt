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
        visible: GlobalState.mode === Mode.View
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: _quizSettings
        // TODO column layout?
        delegate: Rectangle {
          height: ListView.view.height
          width: ListView.view.width
          Text {
            text: name
          }
          Component.onCompleted: console.log(name, settings)
          Column {
            Repeater {
              model: settings
              delegate: Rectangle {
              height: 20
              width: ListView.view.width
                // FIXME loader for different types of settings
                CustomCheckBox {
                    anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
                    checked: modelData.value
                    text: modelData.name
                    onCheckedChanged: modelData.value = (checkState === Qt.Checked)
                }
              }
            }
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
