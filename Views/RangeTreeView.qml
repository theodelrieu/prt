import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "white"
    height: parent.height
    width: parent.width / 4
    property bool interactive: true

    Component {
        id: stackComp
        ListView {
            id: lv
            interactive: root.interactive
            model: _rangeTreeModel.rowCount(__rootIndex)
            clip: true
            snapMode: ListView.SnapToItem
            currentIndex: -1
            highlightMoveDuration: -1
            highlightMoveVelocity: -1

            property var __rootIndex: _rangeTreeModel.rootIndex

            delegate: ItemDelegate {
                property var __modelPersistentIndex: _rangeTreeModel.index(model.index, 0, __rootIndex)
                property var __modelName: _rangeTreeModel.data(__modelPersistentIndex, 257)
                property var __modelType: _rangeTreeModel.data(__modelPersistentIndex, 258)
                property var __hasChildren: _rangeTreeModel.rowCount(__modelPersistentIndex)

                highlighted: ListView.isCurrentItem

                enabled: root.interactive
                width: lv.width
                text: __modelName
                onClicked: {
                    lv.currentIndex = model.index
                    _rangeDisplayer.setRange(__modelPersistentIndex)
                }

                onDoubleClicked: {
                    if (__modelType === "folder" && __hasChildren) {
                        stackView.push(stackComp, { __rootIndex: __modelPersistentIndex }, StackView.Immediate)
                    }
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {

            Button {
                enabled: root.interactive
                Layout.fillWidth: true
                height: 30
                Text {
                    anchors.centerIn: parent
                    text: "Root"
                }

                onClicked: stackView.pop(null, StackView.Immediate)
            }
            Button {
                enabled: root.interactive
                Layout.fillWidth: true
                height: 30
                Text {
                    anchors.centerIn: parent
                    text: "Parent"
                }

                onClicked: stackView.pop(StackView.Immediate)
            }
        }


        StackView {
            id: stackView
            initialItem: stackComp

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
