import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../script/config.js" as WindowConfig

Rectangle {
        id: threeDtoolGroup
        color: "#F9FFFF"
		//opacity: 0.8
        radius: 6
        anchors.leftMargin: 50
        Row {
            anchors.fill: parent
            Repeater {
                model: ListModel {
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/threeD/Hyperspectral_3d_import.png")
                        imageButtonUrlOver: qsTr("qrc:/image/threeD/Hyperspectral_3d_import_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/threeD/Hyperspectral_3d_import_press.png")
                        imageButtonText: qsTr("高光谱3D导入")
                    }
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/import.png")
                        imageButtonUrlOver: qsTr("qrc:/image/import_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/import_press.png")
                        imageButtonText: qsTr("3D导入")
                    }
                    ListElement {
                        imageButtonUrl: qsTr("qrc:/image/add/export.png")
                        imageButtonUrlOver: qsTr("qrc:/image/add/export_over.png")
                        imageButtonUrlPress: qsTr("qrc:/image/add/export_press.png")
                        //imageButtonText: qsTr("导出图像")
						imageButtonText: qsTr("3D导出")
                    }

                }
                Rectangle {
                    color: "transparent"
                    width: 80
                    height: parent.height
                    Rectangle {
                        id: imageButtonRect
                        color: "transparent"
                        radius: 8
                        anchors.fill: parent
                        anchors.topMargin: 2
                        anchors.leftMargin: 18
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

			color: "black"
			font.bold:true
            verticalAlignment: Text.bottom
            text: qsTr("3D分析")
        }
}
