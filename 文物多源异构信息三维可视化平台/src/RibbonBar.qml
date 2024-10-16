import QtQuick 2.0
import an.qml.Controls 1.0
import an.qml.Module 1.0
import "../script/config.js" as WindowConfig

Rectangle {
    id: ribbonBar
    // anchors.fill: parent
    width: parent.width
    //color: "#d3f3ff"
	color: "#F9FFFF"
    signal minimize();
    signal resize();
	signal mddcontrol_show(bool bl);

    function switchTab(name) {
        console.log("receive switch menu msg, name: " + name)
        if(name == "文件"){
            fileTab.visible  = true
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }else if(name == "预处理"){
            fileTab.visible  = false
            areaSelectTab.visible = true
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible  = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }else if(name == "光谱库"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = true
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }else if(name == "颜料提取"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = true
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible = false
        }/*else if(name == "物质检测"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			//lineDrawTab.visible  = false
			//threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = true
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }*/else if(name == "多维分析"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = true
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }else if(name == "符号提取"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = true
            topicMakeTab.visible = false
            helpTab.visible =false
        }else if(name == "线描提取"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = true
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =false
        }
		else if(name == "专题制图"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = true
            helpTab.visible =false
        }else if(name == "3D分析"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = true
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible = false
        }else if(name == "帮助"){
            fileTab.visible  = false
            areaSelectTab.visible = false
            spectrumTab.visible  = false
			pigmentTab.visible  = false
			lineDrawTab.visible  = false
			threeDRetrieveTab.visible = false
            colorRetrieveTab.visible = false
            lineRetrieveTab.visible = false
            symbolicRetrieveTab.visible = false
            topicMakeTab.visible = false
            helpTab.visible =true
        }
		ribbonBar.mddcontrol_show(lineRetrieveTab.visible);
    }

    Component.onCompleted: {
         ribbonBar.messageReceived.connect(switchTab)
    }
    
    function changeState(str) {

        if (str === "normal") {
            mainLeftBk.source = "qrc:/image/ribbonbar_left_bk.png"
            resizeButton.imgUrl = "qrc:/image/maximize.png"
            resizeButton.imgUrlOver="qrc:/image/maximize_over.png"
            resizeButton.imgUrlPress="qrc:/image/resize_over.png"
			minimizeButton.imgUrlPress="qrc:/image/minimize_over.png"
			closeButton.imgUrlPress="qrc:/image/close_over.png"

        } else {
            mainLeftBk.source = "qrc:/image/ribbonbar_left_bk.png"
            resizeButton.imgUrl="qrc:/image/resize.png"
            resizeButton.imgUrlOver="qrc:/image/resize_over.png"
			resizeButton.imgUrlPress="qrc:/image/maximize_over.png"
            minimizeButton.imgUrlPress="qrc:/image/minimize_over.png"
			closeButton.imgUrlPress="qrc:/image/close_over.png"
        }
    }

        Image {
            id: mainLeftBk
            fillMode: Image.Stretch
            width: 425
            smooth: true
            source: "qrc:/image/ribbonbar_left_bk.png"
        }
        Image {
            id: mainMiddleBk
            fillMode: Image.Tile
            x: 425
            width: parent.width - 425 - 846
            smooth: true
            source: "qrc:/image/ribbonbar_middle_bk.png"
        }
        Image {
            id: mainRightBk
            fillMode: Image.Stretch
            x: parent.width - 846
            width: 846
            smooth: true
            source: "qrc:/image/ribbonbar_right_bk.png"
        }

        MessageHub {
            id: messageHub
        }
    /*
    // 放置窗口图标
    Image {
        id: windowIcon
        x: WindowConfig.windowIconLeftMargin
        y: WindowConfig.windowIconTopMargin
        width:WindowConfig.windowIconWidth
        height: WindowConfig.windowIconHeight
        source: "qrc:/image/windowIcon.png"
    }
    */


    // 放置工具栏
    Rectangle {
        id: toolBar
        color: "#f8e9c7"
        anchors.top: parent.top
        anchors.topMargin: 28
        anchors.left: parent.left
        height: 127

		Rectangle{
                id: switchMenuBar
                anchors.top:  parent.top
                anchors.left: parent.left
                width:  parent.width
                height: 25
                color: "red"
                //anchors.fill: parent
                SwitchMenu {
                    color: "red"
                    anchors.fill: parent
                    onActivated:{
                        ribbonBar.switchTab(name)
                    }
                }

            }
	
		Rectangle {
			anchors.top: parent.top
			anchors.left: parent.left
			anchors.topMargin: 25
			anchors.margins: 5
            color: "transparent"
            anchors.fill: parent
			
			FileTab
            {
                id: fileTab
                color: "transparent"
                anchors.fill: parent
            }
            AreaSelectTab
            {
                id: areaSelectTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            SpectrumTab
            {
                id: spectrumTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
			PigmentTab
            {
                id: pigmentTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
			LineDrawTab
            {
                id: lineDrawTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
			ThreeDRetrieveTab
            {
                id: threeDRetrieveTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            ColorRetrieveTab
            {
                id: colorRetrieveTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            LineRetrieveTab
            {
                id: lineRetrieveTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            SymbolicRetrieveTab
            {
                id: symbolicRetrieveTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            TopicMakeTab
            {
                id: topicMakeTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
            HelpTab
            {
                id: helpTab
                color: "transparent"
                anchors.fill: parent
                visible: false
            }
        }
    }

    //最小化按钮
    SimpleButton{
        width: WindowConfig.closeButtonWidth
        height: WindowConfig.closeButtonHeight
        anchors.right: resizeButton.left
        anchors.top: parent.top
        id:minimizeButton
		//anchors.topMargin: 5
		imgUrl: qsTr("qrc:/image/minimize.png")
        imgUrlOver: qsTr("qrc:/image/minimize_over.png")
        onMyButtonClicked: {
            ribbonBar.minimize();
        }
    }
	//还原按钮
    SimpleButton{
        width: WindowConfig.closeButtonWidth
        height: WindowConfig.closeButtonHeight
        anchors.right: closeButton.left
        anchors.top: parent.top
        id: resizeButton
		//anchors.topMargin: 5
		imgUrl: qsTr("qrc:/image/resize.png")
        imgUrlOver: qsTr("qrc:/image/resize_over.png")
        onMyButtonClicked: {
            ribbonBar.resize();
        }
    }

	//关闭按钮
    SimpleButton{
        width: WindowConfig.closeButtonWidth
        height: WindowConfig.closeButtonHeight
        anchors.right: parent.right
        anchors.top: parent.top
        id: closeButton
		//anchors.topMargin: 5
		imgUrl: qsTr("qrc:/image/close.png")
        imgUrlOver: qsTr("qrc:/image/close_over.png")
        onMyButtonClicked: {
            Qt.quit();
        }
    }
}