import QtQuick 2.0
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.15

Rectangle {
    id: panelRect
    color: "yellow"

    property alias absWeightButton: absWeightButton
    property alias baseRangeButton: baseRangeButton
    property Item currentGridItem
    property var baseRange: currentGridItem && currentGridItem.baseRange
    property var subranges: currentGridItem && currentGridItem.subs

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
        }
        RadioButton {
            text: "Subranges"
        }
    }

    Rectangle {
        anchors { top: rangeKindLayout.bottom; bottom: panelRect.bottom; right: panelRect.right; left: panelRect.left }
        color: "purple"
        visible: baseRange && baseRange.name !== ""

        Loader {
            id: handInfoLoader
            sourceComponent: visible ? (baseRangeButton.checked ? baseRangeComp : subrangesComp) : null
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
                    color: baseRange.color
                }
                Text {
                    text: baseRange.weight + "%"
                }
            }
        }

        Component {
            id: subrangesComp
            Column {
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
