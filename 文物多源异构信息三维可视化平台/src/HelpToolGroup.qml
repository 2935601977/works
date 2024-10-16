import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../script/config.js" as WindowConfig

Rectangle {
        id: helpToolGroup
        color: "#F9FFFF"
		//opacity: 0.8
        radius: 6
        anchors.leftMargin: 50
        Row {
            anchors.fill: parent
            Repeater {
                model: ListModel {
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/help/help.png")
                        imageButtonUrlOver: qsTr("qrc:/image/help/help_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/help/help_press.png")
                        imageButtonText: qsTr("帮助")
                    }
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/help/about.png")
                        imageButtonUrlOver: qsTr("qrc:/image/help/about_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/help/about_press.png")
                        imageButtonText: qsTr("关于")
                    }

                }
                Rectangle {
                    color: "transparent"
                    width: 70
                    height: parent.height
                    Rectangle {
                        id: imageButtonRect
                        color: "transparent"
                        radius: 8
                        anchors.fill: parent
                        anchors.topMargin: 2
                        anchors.leftMargin: 8
                        ImageButton {
                            anchors.fill: parent
    //                        buttonWidth: imageButtonWidth
    //                        buttonHeight: imageButtonHeight
    //                        buttonTextHeight: imageButtonTextHeight
                            imgUrl: imageButtonUrl
                            imgUrlOver: imageButtonUrlOver
                            imgUrlPress: imageButtonUrlPress
                            buttonText: imageButtonText
                        }
    //                    MouseArea
    //                    {
    //                        anchors.fill: parent
    //                        anchors.bottomMargin: 20
    //                        hoverEnabled: true
    //                        onClicked:
    //                        {
    //                            console.log("clicked:"+imageButtonUrlPress)
    //                            imgUrl: imageButtonUrlPress
    ////                            myButtonClicked();
    //                        }
    //                        onEntered: {
    ////                            imageButtonRect.color = "red"
    //                            imgUrl: imageButtonUrlOver
    //                            console.log("over:"+imageButtonUrlOver)
    //                        }
    //                        onExited: {
    //                            imageButtonRect.color = "transparent"
    //                        }
    //                    }

                        Behavior on color
                        {
                            ColorAnimation
                            {
                                duration: 300
                            }
                        }

                    }

                }
            }

        }
        Text {
            id: toolGroupText
			anchors.bottom: parent.bottom
            //anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
			
            //font
            //{
           //     family:"微软雅黑"
            //    pointSize: 10
            //}
            //color: "#1e2a5e"
			color: "black"
			font.bold:true
            //horizontalAlignment:  Text.AlignHCenter
            verticalAlignment: Text.bottom
            text: qsTr("帮助")
        }
    }


