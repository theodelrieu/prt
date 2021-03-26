import QtQuick 2.15
import QtQuick.Layouts 1.5

import ".."
import "../Enums"

ColumnLayout {
    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
    Layout.fillWidth: true

    // TODO move in globalstate
    property Item currentGridItem

    Loader {
        sourceComponent: currentGridItem ? (GlobalState.rangeType === RangeType.Base ? baseRangeComp : subrangesComp) : null
    }

    Component {
            id: baseRangeComp
            ColumnLayout {
                Text {
                    text: currentGridItem.handText
                }
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
}
