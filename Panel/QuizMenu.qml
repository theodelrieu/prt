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

    ListView {
        visible: GlobalState.mode === Mode.View
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: _quizSettings
        // TODO column layout?
        delegate: Rectangle {
          height: ListView.view.height
          width: ListView.view.width
          ColumnLayout {
            anchors.fill: parent
            Text {
              text: name
              wrapMode: Text.Wrap
              Layout.fillWidth: true
            }
            Repeater {
              model: settings
              delegate: Rectangle {
              Layout.preferredHeight: 20
              Layout.fillWidth: true
                // FIXME loader for different types of settings
                CustomCheckBox {
                    anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
                    checked: modelData.value
                    text: modelData.text
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
