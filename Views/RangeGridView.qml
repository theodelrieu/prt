import QtQuick 2.15
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.5
import ".."
import "../Enums"

GridView {
    id: gridView
    interactive: false
    currentIndex: -1
    anchors.fill: parent
    cellHeight: parent.height / 13
    cellWidth: cellHeight
    property bool __quizAnswered: false

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
        property double selectedOpacity: (GlobalState.mode === Mode.Quiz && __quizAnswered ? 1.0 : 0.4)
        property alias handText: handText.text
        property bool __isCurrentItem: GridView.isCurrentItem

        color: "#f5eeee"
        opacity: __isCurrentItem ? selectedOpacity : deselectedOpacity

        Component {
            id: baseRangeComp
            Rectangle {
                visible: GlobalState.mode === Mode.View || (GlobalState.mode === Mode.Quiz && cell.__isCurrentItem && gridView.__quizAnswered)
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
                        visible: GlobalState.mode === Mode.View || (GlobalState.mode === Mode.Quiz && cell.__isCurrentItem && gridView.__quizAnswered)

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
            gridView.currentIndex = -1
        }
    }
    Connections {
        target: _quizer
        function onNewQuiz(idx) {
            gridView.currentIndex = idx
            gridView.__quizAnswered = false
        }
    }
    Connections {
        target: _quizer
        function onAnswered() {
            gridView.__quizAnswered = true
        }
    }
}
