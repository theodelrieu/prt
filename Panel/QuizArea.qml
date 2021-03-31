import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

import "../Enums"
import ".."

ColumnLayout {
    id: root

    property alias __text: quizQuestionText.text
    property var __choices: []

    Text {
        id: quizQuestionText
        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        Layout.fillWidth: true
        textFormat: Text.StyledText
        wrapMode: Text.Wrap
    }

    Component {
        id: quizChoicesComp
        GridLayout {
            Repeater {
                model: root.__choices
                delegate: Button {
                    id: choiceButton
                    Layout.preferredWidth: choiceText.width * 1.5
                    Layout.preferredHeight: choiceText.height * 1.5
                    Text {
                        id: choiceText
                        anchors.centerIn: choiceButton
                        text: modelData.text
                        color: modelData.textColor
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
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
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: nextText.implicitWidth * 1.5
            Layout.preferredHeight: nextText.implicitHeight * 1.5
            Text {
                id: nextText
                anchors.centerIn: parent
                text: "Next"
            }
            onClicked: {
                _quizer.next();
            }
        }
    }

    Loader {
        id: loader
    }

    Connections {
        target: _quizer
        function onNewQuiz(idx, txt, choices) {
            root.__text = txt
            root.__choices = choices
            GlobalState.mode = Mode.QuizAsked
        }
        function onAnswered(result) {
            root.__text = result
            GlobalState.mode = Mode.QuizAnswered
        }
    }

    states: [
        State {
            name: "quizAsked"
            when: GlobalState.mode === Mode.QuizAsked
            PropertyChanges {
                target: loader
                sourceComponent: quizChoicesComp
                Layout.fillWidth: true
            }
        },
        State {
            name: "quizAnswered"
            when: GlobalState.mode === Mode.QuizAnswered
            PropertyChanges {
                target: loader
                sourceComponent: quizNextComp
                Layout.fillWidth: true
            }
        }
    ]
}
