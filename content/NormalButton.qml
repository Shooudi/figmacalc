import QtQuick
import QtQuick.Controls.Basic

// digits - Numbers, cancel, dot
Button {
    id: normalButton
    implicitWidth: 60
    implicitHeight: 60

    readonly property color buttonColor: "#B0D1D8"
    readonly property color buttonDownColor: "#04BFAD"
    readonly property color buttonTextColor: "#024873"
    readonly property color buttonTextDownColor: "#FFFFFF"
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
