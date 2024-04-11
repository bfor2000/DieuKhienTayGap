import QtQuick
import QtQuick.Controls
Item {
    Component{
        id:componentSwitch

    ListView{
        interactive:false
        id:viewSwitch
        anchors.fill: parent
        model:Backend.listSwitch(name)
        orientation: ListView.Horizontal
        delegate:listSwitch
        Component{
            id:listSwitch
            Item{
                required property string modelData
                width:viewSwitch.parent?viewSwitch.parent.width/3:0
                height:viewSwitch.parent?viewSwitch.parent.height:0
                Column{
                    anchors.fill: parent
                    Rectangle{
                        width: parent.width
                        height: parent.height/3
                        TextEdit{
                            anchors.centerIn: parent
                            text: modelData
                            font.pointSize: 13
                        }
                    }
                    Rectangle{
                        width: parent.width
                        height: parent.height*2/3
                        Switch{
                            onToggled: Backend.setStatusSwitch(name,modelData,mSwitch.checked)
                            checked: Backend.statusSwitch(name,modelData)
                            rotation: 90
                            anchors.centerIn: parent
                            x:0
                            y:(parent.width-viewSwitch.parent.width/12)/2
                            id:mSwitch
                            indicator: Rectangle {
                            width:viewSwitch.parent?viewSwitch.parent.width/6:0
                            height:viewSwitch.parent?viewSwitch.parent.width/12:0
                            radius: 5
                            border.width: 2
                            Rectangle {
                                y: parent.width/12
                                x:!mSwitch.checked?parent.height*1.3:parent.height/4.7
                                width: parent.width/4
                                height: parent.width/3
                                radius: 5
                                color:  mSwitch.checked ?"#17a81a": "#00000000"
                                border.color: mSwitch.checked ?"#17a81a": "#000000"
                            }
                            }
                        }
                    }
                }
            }
        }
    }
    }
}
