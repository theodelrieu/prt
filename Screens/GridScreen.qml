import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5
import ".."
import "../Enums"
import "../Views"

Rectangle {
    id: gridScreen
    color: "#eddcdc"

    RangeTreeView {
        id: treeView
        interactive: GlobalState.mode === Mode.View
    }

    Rectangle {
        id: mainRect
        anchors { top: parent.top; bottom: parent.bottom; right: parent.right; left: treeView.right }

        Rectangle {
            id: gridRect
            width: Math.min(parent.width * 0.8, parent.height)
            height: width
            anchors { top: parent.top; left: parent.left }

            RangeGridView {
                id: gridView
            }
        }
        Panel {
            anchors { top: parent.top; bottom: parent.bottom; left: gridRect.right; right: parent.right }
        }
    }
    Connections {
        target: _rangeDisplayer
        function onRangeLoaded(name) {
            if (!GlobalState.rangeLoaded)
                GlobalState.rangeLoaded = true
            GlobalState.rangeName = name
        }
    }

}

