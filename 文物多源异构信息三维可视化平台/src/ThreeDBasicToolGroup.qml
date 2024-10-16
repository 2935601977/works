import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../script/config.js" as WindowConfig

Rectangle {
        id: threeDbasicToolGroup
        color: "#F9FFFF"
		//opacity: 0.8
        radius: 6
        anchors.leftMargin: 5
        Row {
            anchors.fill: parent
            Repeater {
                model: ListModel {
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/measure.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/measure_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/measure_press.png")
                        imageButtonText: qsTr("测量")
                    }		
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/area.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/area_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/area_press.png")
                        imageButtonText: qsTr("面积")
                    }				
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/volume.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/volume_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/volume_press.png")
                        imageButtonText: qsTr("体积计算")
                    }
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/3d_Print.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/3d_Print_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/3d_Print_press.png")
                        imageButtonText: qsTr("3D打印")
                    }
				    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/3d_enlarge.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/3d_enlarge_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/3d_enlarge_press.png")
                        imageButtonText: qsTr("放大")
                    }
					ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/3d_narrow.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/3d_narrow_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/3d_narrow_press.png")
                        imageButtonText: qsTr("缩小")
                    }
					ListElement {
                        imageButtonUrl: qsTr("qrc:/image/utilThreeD/rotate.png")
                        imageButtonUrlOver: qsTr("qrc:/image/utilThreeD/rotate_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/utilThreeD/rotate_press.png")
                        imageButtonText: qsTr("旋转")
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
                            imgUrl: imageButtonUrl
                            imgUrlOver: imageButtonUrlOver
                            imgUrlPress: imageButtonUrlPress
                            buttonText: imageButtonText
                        }

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
            anchors.horizontalCenter: parent.horizontalCenter
            //color: "#1e2a5e"
			color: "black"
			font.bold:true
            verticalAlignment: Text.bottom
            text: qsTr("3D基本工具")
        }
    }


