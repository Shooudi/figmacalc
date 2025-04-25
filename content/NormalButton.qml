import QtQuick
//import QtQuick.Layouts
import QtQuick.Controls.Basic

// digits - Numbers, cancel, dot
Button {
    id: normalButton
    implicitWidth: 60
    implicitHeight: 60

    readonly property color buttonColor: "#B0D1D8" // theme1_4
    readonly property color buttonDownColor: "#04BFAD" // theme1_3
    readonly property color buttonTextColor: "#024873" // theme1_1
    readonly property color buttonTextDownColor: "#FFFFFF" // theme1_6
    readonly property int buttonRadius: 50
    readonly property int fontSize: 24
    readonly property string fontFamily: "Open Sans"

    background: Rectangle {
      radius: normalButton.buttonRadius
      color: normalButton.down? buttonDownColor : buttonColor

    }
    contentItem: Text {
        text: normalButton.text
        font.pixelSize: normalButton.fontSize
        font.family: normalButton.fontFamily
        font.weight: 600
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: normalButton.down? buttonTextDownColor : buttonTextColor

    }
}
