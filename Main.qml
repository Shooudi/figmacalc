import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import "content"


Window {
    id: window
    width: 360
    height: 616
    minimumWidth: 360
    minimumHeight: 616
    visible: true
    title: qsTr("Calculator")
    color: "#024873"

    Item {
        id: root
        anchors.fill: parent

        readonly property int margin: 24

        Display {
            id: display
        }

        NumberPad {
            id: numberPad
        }

        ColumnLayout {
            id: portraitMode
            anchors.fill: parent
            visible: true

            LayoutItemProxy {
                target: display
                Layout.fillWidth: true
            }

            LayoutItemProxy {
                target: numberPad
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.topMargin: root.margin
                Layout.bottomMargin: 40
            }
        }

/* - - - - - TODO - - - - -
        RowLayout {
            id: landscapeMode
            anchors.fill: parent
            visible: false

            LayoutItemProxy {
                target: display
            }
            LayoutItemProxy {
                target: numpad
            }
        }*/

    }//root

    Rectangle {
        id: notSupportNotification

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10

        implicitWidth: 100
        implicitHeight: 25

        radius: 20
        color: "#80000000"
        visible: false

        Text {
            anchors.centerIn: parent
            text: "В разработке"
            color: "white"
            font.pixelSize: 12
        }

        function show() {
            visible = true;
            timer.start();
        }

        Timer {
            id: timer
            interval: 2000
            onTriggered: notSupportNotification.visible = false
        }
    }

}//window
