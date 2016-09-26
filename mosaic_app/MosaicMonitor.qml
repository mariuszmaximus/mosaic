import QtQuick 2.0
import MoMosaic 1.0

Item {
    MoMosaicView {
        id: mosaicView
        anchors.fill: parent
        showOutlines: false
        showTargetImage: true
        objectName: "mosaicView"
    }
}
