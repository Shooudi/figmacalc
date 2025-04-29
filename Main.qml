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

}//window
