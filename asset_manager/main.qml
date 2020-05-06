import QtQuick 2.9
import QtQuick.Window 2.2
import QuickUi.Sources 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Text {
        id: name
        width: 200
        height: 200
        anchors.centerIn: parent
        text:AssetManager.getResource("text@222").toString()
    }
}
