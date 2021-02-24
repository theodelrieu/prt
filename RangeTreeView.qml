import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5

C1.TreeView {
    id: treeView
    model: _rangeTreeModel
    anchors.fill: parent

    C1.TableViewColumn {
        title: "Ranges"
        role: "display"
    }

    itemDelegate: Item {
        Text {
            anchors.verticalCenter: parent.VerticalCenter
            text: styleData.value
        }
    }

    onActivated: function (idx) {
        if (treeView.isExpanded(idx))
            treeView.collapse(idx)
        else
            treeView.expand(idx)
    }

    onCurrentIndexChanged: function () {
        _rangeDisplayer.setRange(treeView.currentIndex)
    }
}
