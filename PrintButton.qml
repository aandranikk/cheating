import QtQuick 2.0

Rectangle {
    property alias mouseArea: mouseArea

    height: parent.height - 10
    width: height + 100
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    radius: 5

    color: "Blue"
    Text { anchors.centerIn: parent; text: "Print"; color: "white";
        font.pixelSize: parent.height}

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
