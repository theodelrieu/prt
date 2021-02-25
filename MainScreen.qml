import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5
import "."

Rectangle {
    id: mainScreen
    height: window.height
    width: window.width
    color: "red"

    Rectangle {
        id: treeRect
        visible: GlobalState.mode === Mode.View
        height: parent.height
        width: parent.width / 4
        color: "black"

        RangeTreeView {
            id: treeView
        }
    }

    Rectangle {
        id: mainRect
        anchors { top: parent.top; bottom: parent.bottom; right: parent.right; left: treeRect.right }
        color: "green"

        Rectangle {
            id: gridRect
            width: Math.min(parent.width * 0.8, parent.height)
            height: width
            anchors { top: parent.top; left: parent.left }
            color: "white"

            RangeGridView {
                id: gridView
            }
        }
        Panel {
            id: panel
            currentGridItem: gridView.currentItem
            anchors { top: parent.top; bottom: parent.bottom; left: gridRect.right; right: parent.right }
        }
    }
    Connections {
        target: _rangeDisplayer
        function onRangeLoaded() {
            if (!GlobalState.rangeLoaded)
                GlobalState.rangeLoaded = true
        }
    }
}

