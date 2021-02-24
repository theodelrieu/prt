import QtQuick 2.0

MouseArea {
    id: cellMouseArea
    anchors.fill: parent
    hoverEnabled: true
    onEntered: function () {
        if (!parent.GridView.isCurrentItem)
            parent.deselectedOpacity = 0.6
    }
    onExited: function () {
        if (!parent.GridView.isCurrentItem) {
            parent.deselectedOpacity = 1.0
        }
    }
    onClicked: function() {
        parent.deselectedOpacity = 1.0
        if (parent.GridView.isCurrentItem) {
            parent.GridView.view.currentIndex = -1
        } else {
            parent.GridView.view.currentIndex = parent.gridIndex
        }
    }
}
