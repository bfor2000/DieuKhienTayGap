import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Shapes
import com.company.backend
import QtQml.Models
Item {
    Rectangle{
        y:10
        radius:10
        width: parent.width
        height: parent.height-10
        color: "#96ccffff"
        GridView{
            ListModel{
                id:listDevice
            }
            Connections {
                target: Backend
                function onJsonDocumentChanged() {
                    listDevice.clear()
                    var i=0
                    var device=Backend.listDevice("Device")
                    var model=Backend.listDevice("model")
                    var name=Backend.listDevice("name")
                    console.log("signals")
                    for(i=0;i<name.length;i++)
                        listDevice.append({"device":device[i],"model":model[i],"name":name[i]})
                }
            }
            x:10
            //anchors.margins: 10
            width: parent.width
            height: parent.height
            id:gridHome
            cellWidth: parent.width/3
            cellHeight: parent.height/3
            header:headHome
            model:listDevice
            delegate:Component{
                Rectangle{
                    width: gridHome.cellWidth
                    height: gridHome.cellHeight
                    color:"#00000000"
                    Rectangle {
                        radius: 15
                        border.width: 0
                        //anchors.margins: 10
                        width: parent.width-20
                        height: parent.height-20
                        Column{
                            width:parent.width
                            height: parent.height
                            Rectangle{
                                width:parent.width
                                height:parent.height*2/5
                                color:"#00000000"
                                Column{
                                    anchors.fill: parent
                                Row{
                                    width: parent.width
                                    height: parent.height*3/4
                                    Rectangle{
                                        width: parent.width/5
                                        height: parent.height
                                        color:"#00000000"
                                        Image {
                                            function iconModel(nameModel){
                                                switch (nameModel){
                                                    case "congtac": return "qrc:/asset/image/power-switch.png"
                                                    case "ledmatrix": return "qrc:/asset/image/ledmatrix.png"
                                                }
                                            }
                                            anchors.centerIn: parent
                                            width: 35
                                            height: 35
                                            source: iconModel(model)
                                        }
                                    }
                                    Text{
                                        verticalAlignment: Text.AlignVCenter
                                        width: parent.width*3/5
                                        height: parent.height
                                        horizontalAlignment:Text.AlignLeft
                                        text:name
                                        font.family:"times new roman"
                                        font.bold: true
                                        font.pointSize: 25
                                    }
                                    Rectangle{
                                        width: parent.width/5
                                        height: parent.height
                                        color:"#00000000"
                                        Button{
                                            anchors.centerIn: parent
                                            width: parent.width/2
                                            height: parent.width/2
                                            onClicked:changedName.open()
                                            background: Image {
                                                anchors.fill:parent
                                                fillMode: Image.Stretch
                                                anchors.centerIn: parent
                                                source: "qrc:/asset/image/changedName.png"
                                            }
                                            Popup{
                                                id: changedName
                                                x: -parent.width*6.5
                                                y:parent.height
                                                width: parent.width*8
                                                height: parent.height*2
                                                modal: true
                                                focus: true
                                                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                                Column{
                                                    anchors.fill: parent
                                                Row{
                                                    width: parent.width
                                                    height: parent.height*2/3
                                                    TextInput{
                                                        verticalAlignment: TextInput.AlignVCenter
                                                        horizontalAlignment: TextInput.AlignHCenter
                                                        id:inputchange
                                                        font.family: "times new roman"
                                                        width: parent.width/4*3
                                                        height: parent.height
                                                        font.pointSize: 15
                                                        inputMethodHints: Qt.ImhDigitsOnly|Qt.ImhUppercaseOnly|Qt.ImhLowercaseOnly
                                                        maximumLength: 15
                                                    }
                                                    Rectangle{
                                                        width: parent.width/4
                                                        height: parent.height
                                                    Button{
                                                        anchors.centerIn: parent
                                                        anchors.fill: parent
                                                        contentItem: Text {
                                                            anchors.centerIn: parent
                                                            text: "Chuyển"
                                                            font.family: "times new roman"
                                                            font.pointSize: 8
                                                            horizontalAlignment: Text.AlignHCenter
                                                            verticalAlignment: Text.AlignVCenter
                                                        }
                                                        onClicked:checkChanged(inputchange.getText(0,15))
                                                        function checkChanged(nameChanged){
                                                            if(nameChanged==="") texterror.text=                                                  "*Không thể thay đổi được tên"
                                                            else{
                                                                Backend.setName("name",device,nameChanged)
                                                                changedName.close()
                                                            }
                                                        }
                                                        background: Rectangle{
                                                            anchors.centerIn: parent
                                                            width: parent.width
                                                            height: parent.width/2
                                                            radius: 20
                                                            color:"#3333cc"
                                                            }
                                                        }
                                                    }
                                                }
                                                Text{
                                                    id:texterror
                                                    color: "red"
                                                    font.family: "times new roman"
                                                }
                                                }
                                            }
                                        }
                                    }
                                }
                                Rectangle{
                                    width: parent.width
                                    height: parent.height/5
                                Shape {
                                    id:shape
                                    width: parent.width
                                    height: parent.height/5
                                    ShapePath {
                                        strokeWidth: 1
                                        strokeColor: "darkgray"

                                        startX: 0
                                        startY: shape.parent.height

                                        PathLine {
                                            x: shape.parent.width
                                            y: shape.parent.height
                                        }
                                    }
                                }
                                }
                                }
                            }
                            Rectangle{
                                id:recContent
                                width: parent.width
                                height: parent.height*3/5
                                color:"#00000000"
                                Loader{
                                    function identify(nameModel){
                                        switch(nameModel){
                                            case "congtac": return componentSwitch
                                            case "ledmatrix": return componentLedmatrix
                                        }
                                    }
                                    anchors.fill: parent
                                    sourceComponent: identify(model)
                                }
                                Component{
                                    id:componentLedmatrix
                                    Column{
                                        Rectangle{
                                            width:recContent.width
                                            height:recContent.height
                                        Button{
                                            width:parent.width/2
                                            height:parent.height
                                            onClicked: popup.open()
                                        }
                                        Popup {
                                            id: popup
                                            x: 0
                                            y: 0
                                            width: parent.width
                                            height: parent.height
                                            modal: true
                                            focus: true
                                            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                            }
                                        }
                                        Rectangle{
                                            width:recContent.width
                                            height: recContent.height/4
                                            color: "gray"
                                        }
                                        Rectangle{
                                            width:recContent.width
                                            height: recContent.height/2
                                            color: "#00000000"
                                            Row{
                                                Rectangle{
                                                    color: "#00000000"
                                                    width: recContent.width/3
                                                    height: recContent.height/2
                                                Image {
                                                    fillMode: Image.PreserveAspectFit
                                                    x:0
                                                    y:0
                                                    width: parent.width
                                                    height:80
                                                    source: "qrc:/asset/image/ledmatrix.png"

                                                }
                                                }
                                                Rectangle{
                                                    color: "#00000000"
                                                    width: recContent.width*2/3
                                                    height: recContent.height/2
                                                    Text{
                                                        font.family: "times new roman"
                                                        anchors.centerIn: parent
                                                        text: "<i>Số lượng module:</i>"+"<b> 4</b>"
                                                        font.pointSize: 12
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                Component{
                                    id:componentSwitch
                                ListView{
                                    interactive:false
                                    id:viewSwitch
                                    anchors.fill: parent
                                    model:Backend.listSwitch(device)
                                    orientation: ListView.Horizontal
                                    delegate:Component{
                                        Item{
                                            required property string modelData
                                            width:viewSwitch.parent?viewSwitch.parent.width/3:0
                                            height:viewSwitch.parent?viewSwitch.parent.height:0
                                            Column{
                                                anchors.fill: parent
                                                Rectangle{
                                                    width: parent.width
                                                    height: parent.height/3
                                                        Text{
                                                            horizontalAlignment: Text.AlignHCenter
                                                            verticalAlignment: Text.AlignVCenter
                                                            anchors.fill: parent
                                                            color: "red"
                                                            font.pointSize: 13
                                                            font.family: "times new roman"
                                                            text: "<b>Đổi:  </b>"+"<i>"+Backend.statusSwitch("name",device,modelData)+"</i>"
                                                        }
                                                        MouseArea{
                                                            anchors.fill: parent
                                                            onClicked:popEditName.open()
                                                        }
                                                        Popup {
                                                            id: popEditName
                                                            x: 0
                                                            y: parent.height
                                                            width: parent.width
                                                            height: parent.height*2.5
                                                            modal: true
                                                            focus: true
                                                            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                                            Column{
                                                                anchors.fill: parent
                                                            TextInput{
                                                                id:inputName
                                                                maximumLength: 15
                                                                width: parent.width
                                                                height: parent.height/5*2
                                                                font.family: "times new roman"
                                                                font.pointSize: 13
                                                                inputMethodHints: Qt.ImhDigitsOnly|Qt.ImhUppercaseOnly|Qt.ImhLowercaseOnly
                                                            }
                                                            Button{
                                                                function checkNameChanged(nameDevice,nameKey,nameChanged){
                                                                    if(nameChanged==="") textError.text="*Tên không hợp lệ!"
                                                                    else Backend.setStatusSwitch("name",nameDevice,nameKey,nameChanged)

                                                                }
                                                                text: "Đổi"
                                                                width: parent.width
                                                                height: parent.height/5*2
                                                                onClicked:checkNameChanged(device,modelData,inputName.getText(0,15))
                                                                background: Rectangle {
                                                                    width: parent.width
                                                                    height: parent.height/1.5
                                                                    color: "#00ffff"
                                                                    radius: 8
                                                                }
                                                            }
                                                            Text {
                                                                id:textError
                                                                //text:"*Tên không hợp lệ!"
                                                                width: parent.width
                                                                height: parent.height/5
                                                                font.family: "times new roman"
                                                                font.pointSize: 8
                                                                color:"red"
                                                            }
                                                            }
                                                        }
                                                }
                                                Rectangle{
                                                    width: parent.width
                                                    height: parent.height*2/3
                                                    color:"#00000000"
                                                    Switch{
                                                        onToggled: Backend.setStatusSwitch("data",device,modelData,"",mSwitch.checked)
                                                        checked: Backend.statusSwitch("switch",device,modelData)==="on"?true:false
                                                        rotation: 90
                                                        anchors.centerIn: parent
                                                        x:0
                                                        y:(parent.width-viewSwitch.parent.width/12)/2
                                                        id:mSwitch
                                                        indicator: Rectangle {
                                                        color:"#00000000"
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
                        }
                    }
                }
            }
        }
    }
    Component{
        id:headHome
            Column{
                Text {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                text: qsTr("Xin Chào!")
                font.pointSize: 40
            }
                Text {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                text: qsTr("Danh sách các thiết bị")
                font.pointSize: 35
                color:"Gray"
            }
        }
    }
}
