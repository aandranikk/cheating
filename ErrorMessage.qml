import QtQuick 2.0

Rectangle {
    id: rect
    property alias msg: text.text

    anchors.margins: 20
    anchors.top: parent.top
    anchors.right: parent.right
    height: 150
    width: 250

    color: "red"
    opacity: 0.8
    z: 10
    radius: 10

    Text {
        id: text

        anchors.margins: 10
        anchors.fill: parent

        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        elide: Text.ElideMiddle
        font.pixelSize: 17
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            anim2.wasStoppedManually = true
            anim1.stop()
            anim2.stop()

            parent.opacity = 0.8
        }
        onClicked: {
            //parent.visible = false
            rect.destroy();
        }
    }

    NumberAnimation on opacity { id: anim1; to: 0; duration: 8000 }
    PropertyAnimation on visible {
        id: anim2;
        property bool wasStoppedManually: false
        to: false; duration: anim1.duration
        onRunningChanged: {
            if (!anim2.running && !wasStoppedManually)
                rect.destroy();
        }
    }
}


