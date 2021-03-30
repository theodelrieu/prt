import QtQuick 2.15

Rectangle {
    id: quizChoicesRect
    visible: GlobalState.mode === Mode.Quiz
    color: "white"

    property alias text: quizQuestionText.text
    property var choices: []
    ColumnLayout {
        anchors.fill: parent
        Text {
            id: quizQuestionText
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.maximumWidth: parent.width
            textFormat: Text.StyledText
            wrapMode: Text.Wrap
        }
        Component {
            id: quizChoicesComp
            GridLayout {
                columns: 2
                Repeater {
                    model: quizChoicesRect.choices
                    delegate: Button {
                        Layout.fillWidth: true
                        Text {
                            anchors.centerIn: parent
                            text: modelData.text
                            color: modelData.textColor
                            font.bold: true
                        }
                        onClicked: {
                            _quizer.answer(index)
                        }
                    }
                }
            }
        }
        Component {
            id: quizNextComp
            Button {
                id: quizNextButton
                Text {
                    anchors.centerIn: parent
                    text: "Next"
                }
                onClicked: {
                    _quizer.next();
                }
            }
        }
        Loader {
            id: quizButtonsLoader
            Layout.fillWidth: true
            sourceComponent: panelRect.__quizAnswered ? quizNextComp : quizChoicesComp
        }
    }
}
