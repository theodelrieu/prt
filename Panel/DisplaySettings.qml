import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5

import "../Enums"
import "../Components"
import ".."

Item {
    ColumnLayout {
        id: firstLayout
        Text {
            text: "Weights"
            font.underline: true
        }

        CustomRadioButton {
            checked: true
            text: "Absolute"
            onCheckedChanged: {
                if (checked)
                    GlobalState.weightType = WeightType.Absolute
                else
                    GlobalState.weightType = WeightType.Relative
            }
        }
        CustomRadioButton {
            text: "Relative"
        }
    }

    ColumnLayout {
        anchors.top: firstLayout.bottom
        Text {
            text: "Range kind"
            font.underline: true
        }
        CustomRadioButton {
            checked: true
            text: "Base range"
            onCheckedChanged: {
                if (checked)
                    GlobalState.rangeType = RangeType.Base
                else
                    GlobalState.rangeType = RangeType.Subranges
            }
        }
        CustomRadioButton {
            text: "Subranges"
        }
    }
}
