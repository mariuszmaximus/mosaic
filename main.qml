import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Mosaic Maker")
    id: mainWindow

    property url masterURL: ""
    property var mosaicURLs: []

    ColumnLayout {
        Button {
            id: masterImage
            text: qsTr("Select Target")
            onClicked: masterFileDialog.open();
        }
        Button {
            id: mosaicImages
            text: qsTr("Add Mosaic Images")
            onClicked: mosaicFileDialog.open();
        }
    }

    FileDialog {
        id: masterFileDialog
        title: "Select additional mosaic images"
        folder: shortcuts.pictures
        nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
        selectExisting: true
        selectMultiple: false
        onAccepted: {
            mainWindow.masterURL = masterFileDialog.fileURL
        }
    }

    FileDialog {
        id: mosaicFileDialog
        title: "Select additional mosaic images"
        folder: shortcuts.pictures
        nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
        selectExisting: true
        selectMultiple: true
        onAccepted: {
            mainWindow.mosaicURLs.append(mosaicFileDialog.fileURLs)
        }
    }

    Rectangle {
      id: thumbnailView
      anchors.right: parent.right
      anchors.top: parent.top
      width: 300
      height: 500
      visible: true
      color: "gray"
      GridView {
        anchors.fill: parent
        id: gridView1
        cellWidth: 50
        cellHeight: 50
        delegate: listDelegate
        model: sourceImages
        visible: true
      }
      Component {
        id: listDelegate
        Rectangle {
          id: gridImageWrapper
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
            source: {index == -1 ? '' : "image://imgProvider/" + index}
            smooth: true
            visible: true
            cache: true
          }
        }
      }
    }
}
