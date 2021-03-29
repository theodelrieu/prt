import QtQuick 2.15
import QtQuick.Layouts 1.5

import ".."
import "../Enums"

ColumnLayout {
    id: root

    // TODO move in globalstate
    property Item currentGridItem

    Loader {
        id: loader
    }

    Component {
        id: baseRangeComp
        ColumnLayout {
            Text {
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                text: currentGridItem.handText
            }
            RowLayout {
                Rectangle {
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 30
                    color: currentGridItem.baseRange.color
                }
                Text {
                    text: currentGridItem.baseRange.weight + "%"
                }
            }
        }
    }

    Component {
        id: subrangesComp
        ColumnLayout {
            property var subranges: currentGridItem.subs
            property var baseRange: currentGridItem.baseRange
            Text {
                text: currentGridItem.handText
            }
            Repeater {
                model: subranges
                RowLayout {
                    Rectangle {
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        color: modelData.color
                    }
                    Text {
                        text: modelData.name + ": " + modelData.weight * (GlobalState.weightType === WeightType.Absolute ? baseRange.weight / 100 : 1) + "%"
                    }
                }
            }
        }
    }

    onCurrentGridItemChanged: {
        if (currentGridItem)
            root.state = "gridItemSelected"
        else
            root.state = ""
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
