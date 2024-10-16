import QtQuick 2.0
import "../script/config.js" as WindowConfig

Rectangle {
    id: switchMenu
    //signal menuButtonClicked();
    anchors.fill: parent
    anchors.left: WindowConfig.switchToWinLeftMargin
    color: "#293f50"

    property string menuName: "文件"
    property int i: 0

    signal activated(string name)

    Component.onCompleted: {
        var item = menuRepeter.itemAt(0)
       item.selected = 1;
    }

    Row
    {
       anchors.fill: parent
       anchors.leftMargin: WindowConfig.switchToWinLeftMargin
       spacing: WindowConfig.switchMenuMargin
       Repeater
       {
           id: menuRepeter
           model: [qsTr("文件"),
                   qsTr("预处理"),
                   qsTr("光谱库"),
				   qsTr("颜料提取"),
				   qsTr("线描提取"),
				   qsTr("符号提取"),
                   //qsTr("物质检测"),
                   qsTr("多维分析"),
                   //qsTr("符号提取"),
                   qsTr("专题制图"),
				   qsTr("3D分析"),
                   qsTr("帮助")]
           Rectangle
           {
               property int selected: 0 //selected property
               onSelectedChanged: {
                   if(selected == 0){
                        switchMenuRect.color = "transparent"
                        switchMenuText.color = "white"
                   } else{
                       switchMenuRect.color = "#212121"
                       switchMenuText.color = "yellow"
                   }
               }

               id: bgRect
               color: "transparent"
               width: 50
               height: parent.height
               Rectangle
               {
                   id: switchMenuRect
                   anchors.fill: parent
                   anchors.topMargin: 3
                   radius: 3
                   color: "transparent"
                   Text
                   {
                       id: switchMenuText
                       anchors.centerIn: parent
                       anchors.bottomMargin: 2
                       font
                       {
                           //family:"微软雅黑"
                           pixelSize: 12
                       }
                       color: "white"
                       horizontalAlignment:  Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       text: modelData

                   Behavior on color
                   {
                       ColorAnimation
                       {
                           duration: 300
                       }
                   }
               }
           }

           MouseArea
           {
               anchors.fill: parent
               hoverEnabled: true
                       onClicked:
                       {
                           for(i = 0; i < menuRepeter.count; i++){
                                var item = menuRepeter.itemAt(i)
                               item.selected = 0;
                           }
                           menuName = switchMenuText.text
                           bgRect.selected = 1

                           //send msg to parent for switch ribbon bar
                           console.log(switchMenuText.text + " is clicked...")
                           switchMenu.activated(switchMenuText.text)
                       }
               onEntered: {
                   if(menuName!=switchMenuText.text){
                        switchMenuRect.color = "#212121"
                        switchMenuText.color = "white";
                   }
               }
               onExited: {
                   if(menuName!=switchMenuText.text){
                        switchMenuRect.color = "transparent"
                        switchMenuText.color = "white"
                   }
               }
           }
        }
       }
    }
}
