import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5
import "."

GridView {
    id: gridView
    interactive: false
    currentIndex: -1
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

        property var subs: subranges
        property var baseRange: parentRange
        property int gridIndex: index
        property double deselectedOpacity: 1.0
        property alias handText: handText.text

        color: "#f5eeee"
        opacity: GridView.isCurrentItem ? 0.2 : deselectedOpacity

        Item {
            id: rangeInfoItem
            Component {
                id: baseRangeComp
                Rectangle {
                    visible: GlobalState.mode === Mode.View
                    width: cell.width
                    height: cell.height * (baseRange.weight / 100)
                    color: baseRange.color
                }
            }

            Component {
                id: subrangesComp
                Column {
                    Repeater {
                        model: subs
                        Rectangle {
                            visible: GlobalState.mode === Mode.View
                            property double baseWeight: baseRange.weight / 100
                            width: cell.width
                            height: cell.height * (modelData.weight / 100) * (GlobalState.weightType === WeightType.Absolute ? baseWeight : 1)
                            color: modelData.color
                        }
                    }
                }
            }

            Loader {
                id: rangeInfoLoader
                sourceComponent: (GlobalState.rangeType === RangeType.Base ? baseRangeComp : subrangesComp)
            }
        }

        Text {
            id: handText
            anchors.centerIn: parent
            text: model.name
            fontSizeMode: Text.Fit
        }
        MouseArea {
            id: cellMouseArea
            enabled: GlobalState.rangeLoaded && GlobalState.mode === Mode.View
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
    }

    Connections {
        target: GlobalState
        function onModeChanged() {
            if (GlobalState.mode === Mode.Quiz) {
                gridView.currentIndex = -1
                _quizer.start()
            }
        }
    }
    Connections {
        target: _quizer
        function onNewQuiz(idx, info) {
            gridView.currentIndex = idx
            console.log("Is", gridView.currentItem.handText, "in the", info.name, "range?")
        }
    }
}
