import QtQuick 2.0
import QtQuick.Controls 1.4

// переделать

Item {
    anchors.fill: parent
    visible: false

    Text {
        z: 100
        font.pixelSize: 50
        color: "red"
        text: qsTr("ПЕРЕДЕЛАТЬ РЕДАКТОР")
    }

    function show() {
        visible = true

        mainImage.visible = true
        mainImage.rotation = 0

      //  mainImage.source = "image://ImageProvider/" +
      //          subjects.currentItem.mdata.display + "/" +
      //          themes.currentItem.mdata.display + "/" +
      //          images.currentItem.mdata.display
        mainImage.source = "file://" + currPicDir +
                            images.currentItem.mdata.display
        blackAndWhiteEffect.source = mainImage
    }

    function hide() {
        mainImage.visible = false
        blackAndWhiteEffect.source = null
        visible = false
    }

    Rectangle {
        opacity: 0.8
        color: "green"

        z: 1
        x: controlPanel.x
        anchors.bottom: controlPanel.top
        anchors.bottomMargin: 5
        radius: controlPanel.radius

        width: 75
        height: 30

        Text {
            anchors.centerIn: parent; text: "назад"; color: "black";
            font.pixelSize: parent.height - 10
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                imageEditor.hide()
                mainContent.visible = true
            }
        }
    }

    Item {
        id: imageHolder

        anchors.topMargin: 10
        height: parent.height - (controlPanel.height + controlPanel.anchors.margins*2)
        width: parent.width

        //color: "transparent"

        Image {
            id: mainImage

            anchors.centerIn: parent

            sourceSize.width: parent.width
            sourceSize.height: parent.heigh
            width: parent.width
            height: parent.height

            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }

        ShaderEffect {
            id: blackAndWhiteEffect

            property Item source
            property real threshold: thresholdValueSlider.value

            anchors.centerIn: parent

            width: source.paintedWidth
            height: source.paintedHeight

            visible: !mainImage.visible
            rotation: mainImage.rotation

            ShaderEffectSource { sourceItem: source }

            fragmentShader: "
                uniform float threshold;

                uniform sampler2D source;
                uniform lowp float qt_Opacity;
                varying vec2 qt_TexCoord0;

                void main()
                {
                    vec2 uv = qt_TexCoord0.xy;
                    vec4 orig = texture2D(source, uv);
                    vec3 col = orig.rgb;
                    float y = (11*col.r + 16*col.g + 5*col.b) / 32;
                    //float y = (11*col.r + 16*col.g + 1*col.b) / 28;
                    //y = y < threshold ? y - 0.2 : y + 0.2;
                    gl_FragColor = qt_Opacity * vec4(y, y, y, 1.0);
                }
            "
        }
    }

    Rectangle {
        id: controlPanel

        anchors.margins: 15 //?? x: anchors.margins
        anchors.top: imageHolder.bottom
        height: 70
        width: parent.width - anchors.margins*2
        x: anchors.margins

        color: "black"
        radius: 10

        Row {
            /*Button {
                text: "save"
                onClicked: {
                    imageHolder.grabToImage(function(result) {
                                               result.saveToFile("D:/sh/saved.png",
                                                                 Qt.size(1000,1000))
                                               console.log("saved")
                                         })
                }
            }*/

            Button {
                text: "<-"
                onClicked: { mainImage.rotation -= 90 }
            }

            Button {
                text: "->"
                onClicked: { mainImage.rotation += 90 }
            }

            Button {
                text: "чб"
                onClicked: { mainImage.visible = !mainImage.visible }
            }

            Slider {
                id: thresholdValueSlider

                visible: blackAndWhiteEffect.visible

                width: 300
                value: 0.5
                minimumValue: 0
                maximumValue: 1
                stepSize: 0.01
                onValueChanged: blackAndWhiteEffect.threshold = value
            }
        }
    }
}

