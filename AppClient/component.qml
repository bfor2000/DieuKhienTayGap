import QtQuick
import QtQuick.Layouts
App{
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
