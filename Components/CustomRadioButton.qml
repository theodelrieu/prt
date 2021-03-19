import QtQuick 2.15
import QtQuick.Controls 2.15

RadioButton {
    contentItem: Text {
        text: parent.text
        color: "black"
        leftPadding: parent.indicator.width + parent.spacing
        verticalAlignment: Text.AlignVCenter
    }
}
