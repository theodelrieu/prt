import QtQuick 2.0
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.15
import "."
import "Enums"

Rectangle {
    id: panelRect
    color: "yellow"

    property Item currentGridItem
    property bool __rangeLoaded: false
    property bool __quizAnswered: false

    ColumnLayout {
        id: weightsLayout

        Text {
            text: "Weights"
            font.underline: true
        }

        RadioButton {
            id: absWeightButton
            checked: true
            text: "Absolute"
            onCheckedChanged: {
                if (checked)
                    GlobalState.weightType = WeightType.Absolute
                else
                    GlobalState.weightType = WeightType.Relative
            }
        }
        RadioButton {
            text: "Relative"
        }
    }

    ColumnLayout {
        id: rangeKindLayout
        anchors.top: weightsLayout.bottom
        Text {
            text: "Range kind"
            font.underline: true
        }
        RadioButton {
            id: baseRangeButton
            checked: true
            text: "Base range"
            onCheckedChanged: {
                if (checked)
                    GlobalState.rangeType = RangeType.Base
                else
                    GlobalState.rangeType = RangeType.Subranges
            }
        }
        RadioButton {
            text: "Subranges"
        }
    }

    Rectangle {
        id: rangeNameRect
        color: "green"
        implicitHeight: txt.height
        width: parent.width
        anchors { top: rangeKindLayout.bottom }

        Text {
            id: txt
            text: GlobalState.rangeName
            width: parent.width
            wrapMode: Text.Wrap
        }
    }

    Rectangle {
        id: handInfoRect
        height: (panelRect.height - weightsLayout.height - rangeKindLayout.height) / 3
        anchors { top: rangeNameRect.bottom; right: panelRect.right; left: panelRect.left }
        color: "purple"

        Loader {
            id: handInfoLoader
            sourceComponent: (__rangeLoaded && currentGridItem && (GlobalState.mode === Mode.View || panelRect.__quizAnswered)) ? (baseRangeButton.checked ? baseRangeComp : subrangesComp) : null
        }
    }

    Rectangle {
        id: quizChoicesRect
        visible: GlobalState.mode === Mode.Quiz
        color: "white"
        height: handInfoRect.height
        anchors { top: handInfoRect.bottom; right: panelRect.right; left: panelRect.left }
        property alias text: quizQuestionText.text
        ColumnLayout {
            anchors.fill: parent
            Text {
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                id: quizQuestionText
                Layout.maximumWidth: parent.width
                textFormat: Text.StyledText
                wrapMode: Text.Wrap
            }
            Component {
                id: quizChoicesComp
                RowLayout {
                    Layout.alignment: Qt.AlignBottom
                    Button {
                        id: quizYesButton
                        Layout.fillWidth: true
                        Layout.maximumWidth: quizChoicesRect.width / 2
                        Text {
                            anchors.centerIn: parent
                            text: "Yes"
                        }
                        onClicked: {
                            _quizer.answer(true)
                        }
                    }
                    Button {
                        id: quizNoButton
                        Layout.fillWidth: true
                        Layout.maximumWidth: quizChoicesRect.width / 2
                        Text {
                            anchors.centerIn: parent
                            text: "No"
                        }
                        onClicked: {
                            _quizer.answer(false)
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
                sourceComponent: panelRect.__quizAnswered ? quizNextComp : quizChoicesComp
            }
        }
    }

    Rectangle {
        anchors { bottom: panelRect.bottom; right: panelRect.right; left: panelRect.left; top: quizChoicesRect.bottom }
        color: "cyan"
        Button {
            id: quizButton
            enabled: panelRect.__rangeLoaded
            Text {
                id: quizText
                anchors.centerIn: parent
                text: GlobalState.mode === Mode.View ? "Start quiz" : "Stop quiz"
            }
            anchors.centerIn: parent
            onClicked: function () {
                if (GlobalState.mode === Mode.View) {
                    GlobalState.mode = Mode.Quiz
                    _quizer.start()
                }
                else {
                    GlobalState.mode = Mode.View
                    _quizer.stop()
                }
            }
        }
    }

    Connections {
        target: _rangeDisplayer
        function onRangeLoaded(rangeName) {
            panelRect.__rangeLoaded = true
        }
    }

    Connections {
        target: _quizer
        function onNewQuiz(idx, txt) {
            quizChoicesRect.text = txt
            panelRect.__quizAnswered = false;
        }
    }

    Connections {
        target: _quizer
        function onAnswered(result) {
            quizChoicesRect.text = result
            panelRect.__quizAnswered = true;
        }
    }

    Item {
        Component {
            id: baseRangeComp
            Row {
                Text {
                    text: currentGridItem.handText
                }
                Rectangle {
                    implicitHeight: 30
                    implicitWidth: 30
                    width: panelRect.width / 8
                    height: width
                    color: currentGridItem.baseRange.color
                }
                Text {
                    text: currentGridItem.baseRange.weight + "%"
                }
            }
        }

        Component {
            id: subrangesComp
            Column {
                property var subranges: currentGridItem.subs
                property var baseRange: currentGridItem.baseRange
                Text {
                    text: currentGridItem.handText
                }
                Repeater {
                    model: subranges
                    Row {
                        Rectangle {
                            implicitHeight: 30
                            implicitWidth: 30
                            width: panelRect.width / 8
                            height: width
                            color: modelData.color
                        }
                        Text {
                            text: modelData.name + ": " + modelData.weight * (absWeightButton.checked ? baseRange.weight / 100 : 1) + "%"
                        }
                    }
                }
            }
        }
    }
}
