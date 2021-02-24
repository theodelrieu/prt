import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
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

            onClicked: function (idx) {
                _rangeDisplayer.setRange(idx)
            }

            onDoubleClicked: function (idx) {
                if (treeView.isExpanded(idx))
                    treeView.collapse(idx)
                else
                    treeView.expand(idx)
            }
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

            GridView {
                id: gridView
                interactive: false
                anchors.fill: parent
                cellHeight: parent.height / 13
                cellWidth: cellHeight

                model: _rangeDisplayer
                delegate: Rectangle {
                    id: cell
                    implicitHeight: 30
                    implicitWidth: 30
                    height: gridView.cellHeight * 0.9
                    width: gridView.cellWidth * 0.9
                    color: "lightgray"

                    property var subs: subranges

                    Item {
                        id: rangeInfoItem
                        Component {
                            id: parentRangeComp
                            Rectangle {
                                width: cell.width
                                height: cell.height * (parentRange.weight / 100)
                                color: parentRange.color
                            }
                        }

                        Component {
                            id: subrangesComp
                            Column {
                                Repeater {
                                    model: subs
                                    Rectangle {
                                        width: cell.width
                                        height: cell.height * (modelData.weight / 100)
                                        color: modelData.color
                                    }
                                }
                            }
                        }

                        Loader {
                            id: rangeInfoLoader
                            sourceComponent: subrangesComp

                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: model.name
                        fontSizeMode: Text.Fit
                    }
                }
            }
        }
    }

}
