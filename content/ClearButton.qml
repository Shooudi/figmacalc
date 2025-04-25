import QtQuick
import QtQuick.Controls.Basic

// clear button - clear display
Button {
    id: clearButton
    implicitWidth: 60
    implicitHeight: 60

    readonly property color buttonColor: "#F25E5E" // theme1_5
    readonly property color buttonTextColor: "#FFFFFF" // theme1_6
    readonly property int buttonRadius: 50
    readonly property int fontSize: 24
    readonly property string fontFamily: "Open Sans"

    background: Rectangle {
      radius: clearButton.buttonRadius
      color: clearButton.buttonColor
      opacity: clearButton.down? 1: 0.5
    }
      contentItem: Text {
              text: clearButton.text
              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter
              font.pixelSize: clearButton.fontSize
              font.family: clearButton.fontFamily
              font.weight: 600
              color: clearButton.buttonTextColor
          }



}
