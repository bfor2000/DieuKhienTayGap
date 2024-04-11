import QtQuick
import QtMultimedia
Item {
    Rectangle{
        anchors.fill: parent
        CaptureSession{
            id:capSs
            camera: Camera{}
            videoOutput: videoOutput
            audioInput: AudioInput{
                volume: 1
            }
            audioOutput: audioOutput
            recorder: MediaRecorder{
                id:record
            }
        }
        VideoOutput{
            id:videoOutput
            anchors.fill: parent
        }
        AudioOutput{
            volume: 1
            id:audioOutput
        }
        Component.onCompleted:{
            record.record()
            capSs.camera.start()
        }
        //Component.onDestruction: capSs.camera.stop()
    }
    Component.onDestruction: capSs.camera.stop()
}
