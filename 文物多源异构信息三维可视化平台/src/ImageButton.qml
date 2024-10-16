import QtQuick 2.0
import an.qml.Controls 1.0

Rectangle {
    id: imageButton
    color: "transparent"

    // 属性定义
    property int buttonWidth: 52
    property int buttonHeight: 52
    property int buttonTextHeight: 30
    property string imgUrl: qsTr("")
    property string imgUrlOver: qsTr("")
    property string imgUrlPress: qsTr("")
    property string buttonText: qsTr("")

    Image {
        id: imageButtonImage
        width: buttonWidth
        height: buttonHeight
        anchors.horizontalCenter: parent.top
        source: imgUrl
        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                console.log("over:"+imgUrlOver)
                imageButtonImage.source = imgUrlOver
            }
            onExited: {
                console.log("out:"+imgUrl)
                imageButtonImage.source = imgUrl
            }
            onClicked:
            {
                console.log("clicked:"+imgUrlPress)
                imageButtonImage.source = imgUrlPress
                // mainImage.open()
                messageHub.sendCmd(buttonText)
            }
        }
    }
    Text {
        id: imageButtonText
        height: buttonTextHeight
        anchors.horizontalCenter: imageButtonImage.horizontalCenter
        anchors.top: imageButtonImage.bottom
        anchors.topMargin: 2
        anchors.bottomMargin: 5
        //font
        //{
			//family:"微软雅黑"
        //    pixelSize: 12
        //}
        color: "black"
        horizontalAlignment:  Text.AlignHCenter
        verticalAlignment: Text.bottom
        text: buttonText
    }
}
