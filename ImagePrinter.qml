import QtQuick 2.0

Item {

    visible: false
    width: parent.width/2
    height: parent.height/2
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    Column {
        Text { text: "Введите количество столбцов" ; font.pixelSize: 15}
        TextInput{  id: textEdit1; width: 100; height: 50; font.pixelSize: 20 }
        Text{ text: "Введите количество строк"; font.pixelSize: 15}
        TextInput{    id: textEdit2 ; width: 100; height: 50; font.pixelSize: 20}
        Row {
            Rectangle {
            radius: 5
            color: "grey"
            height: 30
            width:30

            Text {
                anchors.centerIn: parent
                text: "OK"
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    mainContent.visible = true
                    imagePrinter.visible = false
                    backEnd.printClicked(textEdit1.displayText,textEdit2.displayText,themes.model.modelIndex(themes.currentIndex))
                    }
            }
            }

            Rectangle {

            radius: 5
            color: "grey"
            height: 30
            width:50

            Text {
                anchors.centerIn: parent
                text: "Cancel"
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    mainContent.visible = true
                    imagePrinter.visible = false
                    }
            }
            }
        }
    }
}

