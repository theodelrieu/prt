import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5

Rectangle {
    id: content
    height: window.height
    width: window.width
    color: "red"

    Rectangle {
        id: treeRect
        height: content.height
        width: content.width / 4
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
            anchors { top: parent.top; bottom: parent.bottom; left: gridRect.right; right: parent.right }
        }
    }
}

