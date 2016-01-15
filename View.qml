import QtQuick 2.0
import QtQml.Models 2.2


ListView {
    property var onDelegateClicked
    //property alias modelIndex: delegate.index
    //property alias modelCurrentIndex: currentIndex

    clip: true
    highlightFollowsCurrentItem: true

    highlight: Rectangle {
        color: "transparent"

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width - 10
            height: 3

            color: "#333333"
        }
    }

    model: DelegateModel {
        model: dataModelBE
        delegate: Rectangle {
            id: del

            property variant mdata: model

            width: parent.width
            height: 25

            color: "transparent"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    onDelegateClicked()
                }
            }

            Text {
                text: display
                font.pixelSize: parent.height - 10
                color: "black"
                x: 5
            }
        }
    }
}


