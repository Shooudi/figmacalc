pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
  id: controller
  implicitHeight: numbers.height
  implicitWidth: numbers.width

  readonly property int spacing: 24

  Rectangle {
    id: numberPad
    anchors.fill: parent
    color: "transparent"
    //color: "black"

      GridLayout {
      id: numbers
        columns: 4
        rows: 5
        columnSpacing: controller.spacing
        rowSpacing: controller.spacing

      ActionButton { icon.source: "icon/bkt.svg"; objectName: "bkt"; onReleased: notSupportNotification.show() } // todo brackets
      ActionButton { icon.source: "icon/plus_minus.svg"; objectName: "neg"; onReleased: calc.negationPressed() }
      ActionButton { icon.source: "icon/percent.svg"; objectName: "per"; onReleased: calc.percentagePressed() } /////////// todo percent

      ActionButton { icon.source: "icon/division.svg"; objectName: "÷"; onReleased: calc.operatorPressed("÷") }

      NormalButton { text: "7"; onReleased: calc.digitPressed(7) }
      NormalButton { text: "8"; onReleased: calc.digitPressed(8) }
      NormalButton { text: "9"; onReleased: calc.digitPressed(9) }

      ActionButton { icon.source: "icon/multiplication.svg"; objectName: "×"; onReleased: calc.operatorPressed("×")}

      NormalButton { text: "4"; onReleased: calc.digitPressed(4) }
      NormalButton { text: "5"; onReleased: calc.digitPressed(5) }
      NormalButton { text: "6"; onReleased: calc.digitPressed(6) }

      ActionButton { icon.source: "icon/minus.svg"; objectName: "-"; onReleased: calc.operatorPressed("-") }

      NormalButton { text: "1"; onReleased: calc.digitPressed(1) }
      NormalButton { text: "2"; onReleased: calc.digitPressed(2) }
      NormalButton { text: "3"; onReleased: calc.digitPressed(3) }

      ActionButton { icon.source: "icon/plus.svg"; objectName: "+"; onReleased: calc.operatorPressed("+") }

      ClearButton { text: "C"; onReleased: calc.clearPressed() }
      NormalButton { text: "0"; onReleased: calc.digitPressed(0) }
      NormalButton { text: "."; onReleased: calc.decimalPressed() }

      ActionButton {
      id: equalsBtn
        icon.source: "icon/equal.svg"
        text: "="

            property bool isLongPress: false
            Timer {
                id: longPressTimer
                interval: 4000
                onTriggered: {
                    equalsBtn.isLongPress = true
                    calc.handleEqualsPressed(true)
                }
            }

            onPressed: longPressTimer.start()
            onReleased: {
                longPressTimer.stop()
                if (!equalsBtn.isLongPress) {
                    calc.handleEqualsPressed(false)
                }
                equalsBtn.isLongPress = false
            }
      }
    }
  } //Rectangle
}
