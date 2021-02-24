import QtQuick 2.0
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.15

Rectangle {
    id: panelRect
    color: "yellow"

    property alias absWeightButton: absWeightButton
    property alias baseRangeButton: baseRangeButton

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
    }
}
