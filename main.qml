import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQml.Models 2.2


ApplicationWindow {
    id: mainWindow

    visible: true
    width: 1100
    height: 800
    title: qsTr("Hello World")

    Component.onCompleted: {
        subjects.currentIndex = -1
        themes.currentIndex = -1
    }

    // необходимо для "обнуления" view изображений, чтобы не было лишних запросов к ImageProvider'у
    //  при смене темы и предмета
    ListModel { id: emptyModel }

    //*********************************************************************************************//
    //***                                   mainContent                                          **//
    //*********************************************************************************************//

    // надо "причесать" код, добавив компоненты, если успеем (сделано: Header)(...View)

    Item {
        id: mainContent
        anchors.fill: parent

    //*********************************************************************************************//
    //***                                   subjects                                             **//
    //*********************************************************************************************//

    Rectangle {
        id: subjectsContainer

        anchors.leftMargin: 5

        width: 200
        height: parent.height * 0.3

        color: "#eeeeee"

        Header {
            id: subjectsHeader
            title: "Предметы"
            adderFunction: (function(subjectName) {
                var msg = backEnd.addSubject(subjectName)
                if (msg != "") {
                    var m = Qt.createQmlObject("ErrorMessage {}", mainContent)
                    m.msg = msg
                }
            })
        }

        ListView {
            id: subjects

            anchors.top: subjectsHeader.bottom
            anchors.bottom: parent.bottom
            width: parent.width

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
                    property variant mdata: model

                    width: parent.width
                    height: 25

                    color: "transparent"

                    DeleteButton {
                        id: deleteSubject
                        z: 3
                        mouseArea.onDoubleClicked: {
                            subjects.currentIndex = -1
                            backEnd.deleteSubject(subjects.model.modelIndex(index))
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //images.visible = false
                            images.model = emptyModel
                            backEnd.subjectClicked(subjects.model.modelIndex(index))

                            subjects.currentIndex = index

                            if (model.hasModelChildren) {
                                themes.currentIndex = -1

                                //themes.model.rootIndex = subjects.model.modelIndex(index)
                                //themes.visible = true
                            }
                            else {
                                //themes.visible = false
                            }
                        }

                        hoverEnabled: true
                        onEntered: {
                            deleteSubject.visible = true
                        }
                        onExited: {
                            deleteSubject.visible = false
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
    }

    //*********************************************************************************************//
    //***                                   themes                                               **//
    //*********************************************************************************************//
    Rectangle {
        id: themesContainer

        anchors.top: subjectsContainer.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: 200

        color: "#eeeeee"

        Header {
            id: themesHeader
            title: "Темы"
            addButtonVisible: subjects.currentIndex != -1
            adderFunction: (function(themeName) {
                var msg = backEnd.addTheme(subjects.model.modelIndex(subjects.currentIndex), themeName)
                if (msg != "") {
                    var m = Qt.createQmlObject("ErrorMessage {}", mainContent)
                    m.msg = msg
                }
                else {
                    // без этого themes не становится видимым, если список изначально был пуст
                    var ci = subjects.currentIndex
                    subjects.currentIndex = -1
                    subjects.currentIndex = ci

                    //themes.model.rootIndex = subjects.model.modelIndex(subjects.currentIndex)
                    //themes.visible = true
                }
            })
        }

        ListView {
            id: themes

            visible: subjects.currentIndex !== -1 && subjects.currentItem.mdata.hasModelChildren

            anchors.top: themesHeader.bottom
            anchors.bottom: parent.bottom
            width: parent.width

            clip: true
            highlightFollowsCurrentItem: true

            highlight: Rectangle {
                color: "transparent"

                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: parent.width - 10
                    height: 3

                    color: "black"
                }
            }

            model: DelegateModel {
                model: dataModelBE

                rootIndex: subjects.model.modelIndex(subjects.currentIndex)

                delegate: Rectangle {
                    property variant mdata: model

                    width: parent.width
                    height: 25

                    color: "transparent"

                    DeleteButton {
                        id: deleteTheme
                        z: 3
                        mouseArea.onDoubleClicked: {
                            themes.currentIndex = -1
                            backEnd.deleteTheme(themes.model.modelIndex(index))
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            images.model = emptyModel
                            backEnd.themeClicked(themes.model.modelIndex(index))
                            themes.currentIndex = index

                            if (model.hasModelChildren)
                            {
                                //imagesModel.rootIndex = themes.model.modelIndex(index)
                                images.model = imagesModel
                                //images.visible = true

                                images.currentIndex = -1
                            }
                            else
                            {
                                //images.visible = false
                            }
                        }

                        hoverEnabled: true
                        onEntered: {
                            deleteTheme.visible = true
                        }
                        onExited: {
                            deleteTheme.visible = false
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
    }

    //*********************************************************************************************//
    //***                                   images                                               **//
    //*********************************************************************************************//
    DelegateModel {
        id: imagesModel
        model: dataModelBE

        rootIndex: themes.model.modelIndex(themes.currentIndex)

        delegate: Rectangle {
            id: imageDelegate
            property variant mdata: model

            width: images.cellWidth
            height: images.cellHeight
            z: 1

            color: "transparent"

            Image {
                id: page

                z: 2
                x: 10
                y: 5
                width: parent.width - 20
                height: parent.height - 20
                sourceSize.width: width
                sourceSize.height: height

                asynchronous: true
                source: "image://ImageProvider/" +
                        subjects.currentItem.mdata.display + "/" +
                        themes.currentItem.mdata.display + "/" +
                        display

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onDoubleClicked: {
                        images.currentIndex = index

                        mainContent.visible = false
                        imageEditor.show()
                    }
                    onClicked: {
                        imageDelegate.state = imageDelegate.state == "selected" ? "" : "selected"
                        backEnd.selectImage(images.model.modelIndex(index))
                    }

                    onEntered: {
                        imageDelegate.color = "#cccccc"
                    }
                    onExited: {
                        if (imageDelegate.state != "selected")
                            imageDelegate.color = "transparent"
                    }
                }
            }

            Text {
                anchors.top: page.bottom
                anchors.horizontalCenter: page.horizontalCenter

                text: display
                font.pixelSize: 13
                color: "black"
            }

            states: [
                State {name: "selected"; PropertyChanges {target: imageDelegate; color: "#cccccc"}}
            ]
        }
    }

    Rectangle {
        id: imagesContainer

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: subjectsContainer.right
        anchors.right: parent.right
        anchors.leftMargin: 5

        color: "#eeeeee"

        Rectangle {
            id: imageHeader

            width: parent.width
            height: 30

            color: "#333333"

            Text {
                text: "Страницы"
                anchors.centerIn: parent; color: "white";
                font.pixelSize: parent.height - 10
            }

            AddButton {
                id: addButton

                anchors.left: parent.left
                anchors.right: undefined
                anchors.leftMargin: 5

                visible: themes.currentIndex != -1
                mouseArea.onClicked: {
                    fileDialog.visible = true
                }
            }

            DeleteButton {
                visible: themes.currentIndex != -1
                anchors.left: addButton.right
                anchors.right: undefined
                anchors.leftMargin: 5

                mouseArea.onDoubleClicked: {
                    backEnd.deleteSelectedImages()
                }
            }
        }

        GridView {
            id: images

            model: emptyModel

            anchors.margins: 5
            anchors.top: imageHeader.bottom
            anchors.bottom: parent.bottom
            width: parent.width

            cellWidth: 220
            cellHeight: 230

            visible: themes.visible &&
                     themes.currentIndex !== -1 && themes.currentItem.mdata.hasModelChildren

            clip: true
            highlightFollowsCurrentItem: true
        }
    }
    }

    //*********************************************************************************************//
    //***                             image editor                                               **//
    //*********************************************************************************************//

    ImageEditor { id: imageEditor }

    FileDialog {
        id: fileDialog

        visible: false
        selectMultiple: true
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)" ]

        onAccepted: {
            var success = false
            var themesIndex = themes.model.modelIndex(themes.currentIndex)
            console.log(themesIndex)
            for (var i = 0; i < fileDialog.fileUrls.length; ++i)
            {
                var msg = backEnd.addImage(themesIndex, fileDialog.fileUrls[i])
                if (msg != "") {
                    var m = Qt.createQmlObject("ErrorMessage {}", mainContent)
                    m.msg = msg
                }
                else success = true
            }

            if (success) {
                // без этого themes не становится видимым, если список изначально был пуст
                var ci = themes.currentIndex
                themes.currentIndex = -1
                themes.currentIndex = ci
                //imagesModel.rootIndex = themesIndex
                images.model = imagesModel
                //images.visible = true
            }
        }
    }
}









