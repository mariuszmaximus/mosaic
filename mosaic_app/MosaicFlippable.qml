import QtQuick 2.7
import MoMosaic 1.0


Rectangle {
    anchors {
        topMargin: 10
        bottomMargin: 10
        leftMargin: 10
        rightMargin: 10
    }

    Component {
        id: listDelegate
        Rectangle {
            width: gridView1.cellWidth
            height: gridView1.cellHeight
            color: "gray"
            Image {
                id: frontIcon
                asynchronous: true;
                anchors.centerIn: parent
                sourceSize.width: gridView1.cellWidth - 2
                sourceSize.height: gridView1.cellHeight - 2
                fillMode: Image.PreserveAspectFit
                source: {index == -1 ? '' : "image://imageProvider/" + index}
                smooth: true
                visible: true
                cache: true
            }
        }
    }

    Rectangle {
        id: thumbnailView
        anchors.fill: parent
        visible: true
        color: "gray"
        GridView {
            anchors.fill: parent
            id: gridView1
            cellWidth: 50
            cellHeight: 50
            delegate: listDelegate
            model: mosaicImages
            visible: true
        }
    }
}
