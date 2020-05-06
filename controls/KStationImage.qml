import QtQuick 2.0
import QuickUi.Sources 1.0

Item {
    property alias fitType: image.fillMode
    property var src: null
    property int index: 0

    Image {
        id: image
        anchors.fill: parent
        source: AssetManager.getResource(src,index)
    }
}
