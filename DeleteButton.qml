import QtQuick 2.0

Rectangle {
    property alias mouseArea: mouseArea

    visible: false
    height: parent.height - 10
    width: height
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    radius: 5

    color: "red"
    Text { anchors.centerIn: parent; text: "-"; color: "white";
        font.pixelSize: parent.height + 5}

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        //property int usageMessageShownCount: 0;

        onClicked: {
            var msg = Qt.createQmlObject("Message {}", mainContent)
            msg.msg = "Для удаления кликните дважды."
        }
    }
}


