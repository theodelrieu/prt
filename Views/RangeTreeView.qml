import QtQuick 2.15
import QtQuick.Controls 1.4 as C1

// TODO replace with something else since TreeView is not in Controls2?
C1.TreeView {
    id: treeView
    model: _rangeTreeModel
    alternatingRowColors: false

    C1.TableViewColumn {
        id: treeColumn
        title: "Ranges"
        role: "display"
        width: 500
    }

    itemDelegate: Item {
        Text {
            text: styleData.value
        }
    }

    onActivated: function (idx) {
        if (treeView.isExpanded(idx))
            treeView.collapse(idx)
        else
            treeView.expand(idx)
    }
    Timer {
        id: resizeToColumnsTimer
        interval: 4000
        repeat: false
        onTriggered: {
            console.log("before width =", treeColumn.width)
            treeView.resizeColumnsToContents();
            console.log("after width =", treeColumn.width)
        }
    }

    onExpanded: {
        // this is broken
        resizeToColumnsTimer.start();
    }

    onCurrentIndexChanged: function () {
        _rangeDisplayer.setRange(treeView.currentIndex)
    }
}
