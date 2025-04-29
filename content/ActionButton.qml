import QtQuick
//import QtQuick.Layouts
import QtQuick.Controls.Basic

// operations - plus, minus, etc..
Button {
    id: actionButton
    implicitWidth: 60
    implicitHeight: 60
    icon.width: 30
    icon.height: 30
    icon.color: "transparent"
    display: Button.IconOnly

    readonly property color buttonColor: "#0889A6"
    readonly property color buttonDownColor: "#F7E425"
    readonly property int buttonRadius: 50
    readonly property int fontPointSize: 24

    background: Rectangle {
      radius: actionButton.buttonRadius
      color: actionButton.down? buttonDownColor :  buttonColor
    }
}
