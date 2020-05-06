import QtQuick 2.0
import QuickUi.Sources 1.0

Item {

    property alias hAlignment: label.horizontalAlignment
    property alias vAlignment: label.verticalAlignment
    property alias rotate: label.rotation
    property var textString
    property alias textColor: label.color
    property alias font: label.font

    Text {
        id:label
        antialiasing: true
        anchors.fill: parent
        text: AssetManager.getResource(textString)
    }

}
