import QtQuick 2.0

Rectangle {
    property alias mouseArea: mouseArea

    height: parent.height - 10
    width: height
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    radius: 5

    color: "green"
    Text { anchors.centerIn: parent; text: "+"; color: "white";
        font.pixelSize: parent.height + 5}

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}

