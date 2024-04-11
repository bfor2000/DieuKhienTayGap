import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import com.company.backend
Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Client Tcp")
    RowLayout {
        spacing: 0
        anchors.fill: parent
        Rectangle {
            color: "white"
            Layout.preferredWidth: 200
            Layout.fillHeight: true

            ListView {
                anchors.topMargin: 10
                id:listBar
                anchors.fill: parent
                interactive:false
                highlight:Rectangle{
                    x:10
                    anchors.margins: 10
                    color: "#ccf2ff"
                    radius: 10
                }
                model: ContentBar{}
                delegate:Component{
                    Item {
                        width:180
                        height:50
                        Row{
                            Rectangle{
                                id:hcn
                                width:70
                                height:50
                                color:"#00000000"
                                Image {
                                    anchors.centerIn: hcn
                                    width:35
                                    height: 35
                                    source: image
                                }
                            }
                            Text {
                                horizontalAlignment:Text.AlignHCenter
                                font.pointSize: 24
                                text: name
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                listBar.currentIndex = index
                                //Backend.getDevice()
                            }
                        }
                    }
                }
                onCurrentIndexChanged: loadPage(model.get(listBar.currentIndex).name)
            }
        }

        Rectangle {
            anchors.topMargin: 10
            radius: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            StackView{
                pushEnter: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 0
                        to:1
                        duration: 50
                    }
                }
                pushExit: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 1
                        to:0
                        duration: 100
                    }
                }
                popEnter: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 0
                        to:1
                        duration: 150
                    }
                }
                popExit: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 1
                        to:0
                        duration: 200
                    }
                }
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom:  parent.bottom
                anchors.top: parent.top
                id:stackPage
                initialItem: home
            }
            Component{
                id:home
                Home{}
            }
            Component{
                id:live
                Live{}
            }
            Component{
                id:setting
                Setting{}
            }
        }
    }
    function loadPage(page){
        switch(page){
            case "Home": stackPage.push(home)
                Backend.jsonDocumentChanged()
                break
            case "Camera": stackPage.push(live)
                break
            case "Setting": stackPage.push(setting)
                break
        }
    }
}


