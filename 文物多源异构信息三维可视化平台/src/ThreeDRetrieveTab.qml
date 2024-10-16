import QtQuick 2.0

Rectangle {
    color: "transparent"
    anchors.fill: parent
    ThreeDRetrieveGroup {
        id:groupOne
        width: 240
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
    }
     ThreeDBasicToolGroup {
		id:threedTools
        width: 490
        height: parent.height
        anchors.left: groupOne.right
        anchors.top: parent.top
		anchors.leftMargin: 10
	}
	Rectangle {
        radius: 6
		color: "#F9FFFF"
		width: 630
		height: parent.height
		anchors.top: parent.top
		anchors.left: threedTools.right
		anchors.leftMargin: 10
		BasicToolGroup {
			id:printTools
			width: 280
			height: parent.height
			anchors.left: parent.left
			anchors.top: parent.top
		}
		ZoomToolGroup {
			id:zoomTools
			width: 350
			height: parent.height
			anchors.left: printTools.right
			anchors.top: parent.top
			anchors.leftMargin: 0
		}
		Text {
			anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            //color: "#1e2a5e"
			color: "black"
			font.bold:true
            verticalAlignment: Text.bottom
			text: qsTr("高光谱基本工具")
        }
	}
}

