import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    id: display
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.maximumHeight: 200
    Layout.alignment: Qt.AlignTop

    readonly property color backgroundColor: "#04BFAD"

    Rectangle {
        anchors.fill: parent
        color: display.backgroundColor
        bottomLeftRadius: 20
        bottomRightRadius: 20

        ColumnLayout {
            anchors.fill: parent
            anchors.rightMargin: 40
            anchors.topMargin: 40
            anchors.leftMargin: 40
            spacing: 10

            Text {
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                text: calc.expression
                font.pixelSize: 20
                font.weight: 600
                font.family: "Open Sans"
                font.letterSpacing: 0.5
                color: "white"
                fontSizeMode: Text.Fit
                minimumPixelSize: 12
                wrapMode: Text.WrapAnywhere
                maximumLineCount: 3
                horizontalAlignment: Text.AlignRight
                elide: Text.ElideNone
            }

            Text {
                Layout.bottomMargin: 8
                Layout.fillWidth: true
                Layout.preferredHeight: 60
                text: calc.result || "0"
                font.pixelSize: 50
                font.weight: 600
                font.family: "Open Sans"
                font.letterSpacing: 0.5
                color: "white"
                fontSizeMode: Text.Fit
                minimumPixelSize: 12
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignBottom
                elide: Text.ElideNone
            }
        }
    }

        Rectangle {
            id: secretPage
            implicitWidth: 200
            implicitHeight: 100
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 10
            }
            color: "#0889A6"
            radius: 20
            visible: false
            Text {
                anchors.fill: parent
                text: "Секретное меню"
                anchors.top: patent.top
                anchors.topMargin: 10
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                font.pixelSize: 12
                font.bold: true
            }

                Button {
                    anchors.centerIn: parent
                    text: "Close"
                    onClicked: secretPage.visible = false
                }
            }

                Connections {
                    target: calc
                    onSecretPageRequested: {
                        secretPage.visible = true
                    }
                }
            }



