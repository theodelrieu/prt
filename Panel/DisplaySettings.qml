import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5

import "../Enums"
import "../Components"
import ".."

Item {
    Layout.fillWidth: true

    Text {
        text: GlobalState.rangeName
        Layout.fillWidth: true
        wrapMode: Text.Wrap
    }
    Text {
        text: "Weights"
        font.underline: true
    }
    Item {
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

    Text {
        text: "Range kind"
        font.underline: true
    }

    Item {
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
