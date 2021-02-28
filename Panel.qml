import QtQuick 2.0
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.15
import "."

Rectangle {
    id: panelRect
    color: "yellow"

    property Item currentGridItem
    property bool __rangeLoaded: false

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
    ColumnLayout{
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
        id: handInfoRect
        height: (panelRect.height - rangeKindLayout.height) / 2
        anchors { top: rangeKindLayout.bottom; right: panelRect.right; left: panelRect.left }
        color: "purple"

        Loader {
            id: handInfoLoader
            sourceComponent: (__rangeLoaded && currentGridItem && GlobalState.mode === Mode.View) ? (baseRangeButton.checked ? baseRangeComp : subrangesComp) : null
        }
    }

    Rectangle {
        anchors { bottom: panelRect.bottom; right: panelRect.right; left: panelRect.left; top: handInfoRect.bottom }
        color: "cyan"
        Button {
            id: quizButton
            enabled: panelRect.__rangeLoaded
            anchors.centerIn: parent
            Text {
                id: quizText
                anchors.centerIn: parent
                text: GlobalState.mode === Mode.View ? "Start quiz" : "Stop quiz"
            }
            onClicked: function () {
                if (GlobalState.mode === Mode.View)
                    GlobalState.mode = Mode.Quiz
                else
                    GlobalState.mode = Mode.View
            }
        }
    }

    Connections {
        target: _rangeDisplayer
        function onRangeLoaded(rangeName) {
            panelRect.__rangeLoaded = true
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
