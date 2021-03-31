import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5

import "../Enums"
import "../Components"
import ".."

ColumnLayout {
    ButtonGroup {
        id: weightButtonGroup
    }

    ButtonGroup {
        id: rangeKindButtonGroup
    }

    Text {
        text: GlobalState.rangeName
        Layout.fillWidth: true
        wrapMode: Text.Wrap
    }

    Text {
        text: "Weights"
        font.underline: true
    }

    CustomRadioButton {
        checked: true
        text: "Absolute"
        ButtonGroup.group: weightButtonGroup
        onCheckedChanged: {
            if (checked)
                GlobalState.weightType = WeightType.Absolute
            else
                GlobalState.weightType = WeightType.Relative
        }
    }

    CustomRadioButton {
        text: "Relative"
        ButtonGroup.group: weightButtonGroup
    }

    Text {
        text: "Range kind"
        font.underline: true
    }

    CustomRadioButton {
        checked: true
        text: "Base range"
        ButtonGroup.group: rangeKindButtonGroup
        onCheckedChanged: {
            if (checked)
                GlobalState.rangeType = RangeType.Base
            else
                GlobalState.rangeType = RangeType.Subranges
        }
    }

    CustomRadioButton {
        text: "Subranges"
        ButtonGroup.group: rangeKindButtonGroup
    }
}
