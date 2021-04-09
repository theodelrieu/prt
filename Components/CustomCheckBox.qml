import QtQuick
import QtQuick.Controls

CheckBox {
    contentItem: Text {
        text: parent.text
        color: "black"
        leftPadding: parent.indicator.width + parent.spacing
        verticalAlignment: Text.AlignVCenter
    }
}
