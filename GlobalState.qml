pragma Singleton

import QtQuick 2.0
import "Enums"

QtObject {
    property int mode: Mode.View
    property int rangeType: RangeType.Base
    property int weightType: WeightType.Absolute
    property bool rangeLoaded: false
    property string rangeName
}
