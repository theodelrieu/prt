import QtQuick 2.0
import QtQuick.Controls 1.4 as C1

Rectangle {
    C1.TreeView {
        id: treeView
        C1.TableViewColumn {
            title: "Ranges"
            role: "display"
            width: 180
        }
        model: _rangeTreeModel
        itemDelegate: Item {
            Text {
                anchors.verticalCenter: parent.VerticalCenter
                text: styleData.value
            }
        }
    }
}
