import QtQuick 2.0

Item {
    property alias fitType: image.fillMode
    property alias src: image.source

    Image {
        id: image
        anchors.fill: parent
    }
}
