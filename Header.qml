import QtQuick 2.0

Rectangle {
    id: header

    property alias title: title.text
    property var adderFunction
    property alias addButtonVisible: addButton.visible

    width: parent.width
    height: 30

    color: "#333333"

    Text {
        id: title
        anchors.centerIn: parent; text: title; color: "white";
        font.pixelSize: parent.height - 10
    }

    AddButton {
        id: addButton
        mouseArea.onClicked: {
            if (!adder.visible)
            {
                title.visible = false
                adder.visible = true
                textInput.forceActiveFocus()
            }
            else
                textInput.onAccepted()
        }
    }

    Rectangle {
        id: adder
        height: parent.height - 7
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: addButton.left
        anchors.left: parent.left
        anchors.margins: 5
        radius: 5
        visible: false
        z:2
        color: "#eeeeee"

        PropertyAnimation on color {
            id: anim
            from: "red"
            to: "#eeeeee"
            duration: 1000
            //paused: true
        }

        TextInput{
            id: textInput
            anchors.fill: parent
            anchors.leftMargin: 14
            anchors.rightMargin: 14

            clip: true

            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 22
            Text {
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                visible: !(parent.text.length || parent.inputMethodComposing)
                font: parent.font
                text: ""
            }

            function checkInput()
            {
                return textInput.text[0] != ' ' // что-то ещё надо?
            }

            function hide()
            {
                textInput.text = ""
                adder.visible = false
                title.visible = true
            }

            onAccepted: {
                if (textInput.text == "")
                    hide()
                else if (checkInput())
                {
                    adderFunction(textInput.text)
                    hide()
                }
                else
                    anim.restart()
            }
        }
    }
}


