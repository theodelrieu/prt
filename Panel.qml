import QtQuick 2.0
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.15
import "."
import "Enums"
import "Panel"

Rectangle {
    id: root

    ColumnLayout {
        anchors.fill: parent

        DisplaySettings {
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
        }

        HandInfo {
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
        }

        QuizArea {
            visible: GlobalState.mode !== Mode.View
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
        }

        Item {
            // spacer item
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        QuizMenu {
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
        }
    }
}
