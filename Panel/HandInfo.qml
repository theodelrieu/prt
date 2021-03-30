import QtQuick 2.15
import QtQuick.Layouts 1.5

import ".."
import "../Enums"

ColumnLayout {
    id: root

    Loader {
        id: loader
    }

    Component {
        id: baseRangeComp

        ColumnLayout {
            Text {
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                text: GlobalState.currentGridItem.handText
            }
            RowLayout {
                Rectangle {
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 30
                    color: GlobalState.currentGridItem.baseRange.color
                }
                Text {
                    text: GlobalState.currentGridItem.baseRange.weight + "%"
                }
            }
        }
    }

    Component {
        id: subrangesComp

        ColumnLayout {
            property var __subranges: GlobalState.currentGridItem.subs
            property var __baseRange: GlobalState.currentGridItem.baseRange
            Text {
                text: GlobalState.currentGridItem.handText
            }
            Repeater {
                model: __subranges
                RowLayout {
                    Rectangle {
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        color: modelData.color
                    }
                    Text {
                        text: modelData.name + ": " + modelData.weight * (GlobalState.weightType === WeightType.Absolute ? __baseRange.weight / 100 : 1) + "%"
                    }
                }
            }
        }
    }

    Connections {
        target: GlobalState

        function onCurrentGridItemChanged() {
            if (GlobalState.currentGridItem && (GlobalState.mode === Mode.View || GlobalState.mode === Mode.QuizAnswered))
                root.state = "gridItemSelected"
            else
                root.state = ""
        }
    }

    states: [
        State {
            name: "gridItemSelected"
            PropertyChanges {
                target: loader
                sourceComponent: GlobalState.rangeType === RangeType.Base ? baseRangeComp : subrangesComp
            }
        }
    ]
}
