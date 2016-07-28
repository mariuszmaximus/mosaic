import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0


ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600

    ColumnLayout {
        Button {
            text: qsTr("Select Target")
            onClicked: targetFileDialog.open();
        }
        Button {
            text: qsTr("Add Mosaic Images")
            onClicked: mosaicFileDialog.open();
        }
    }

    property var targetURL

    FileDialog {
        id: targetFileDialog
        title: "Select the mosaic target image"
        nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        folder: shortcuts.pictures
        onAccepted: {
            console.log(targetFileDialog.fileUrl)
            mainWindow.targetURL = targetFileDialog.fileUrl
        }
    }

    FileDialog {
        id: mosaicFileDialog
        title: "Select additional mosaic images"
        nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
        selectExisting: true
        selectMultiple: true
        selectFolder: false
        modality: Qt.NonModal
        folder: shortcuts.pictures
        onAccepted: {
            console.log(mosaicFileDialog.fileUrls)
            mosaicImages.imagesAdded(mosaicFileDialog.fileUrls)
        }
    }

    Rectangle {
      id: thumbnailView
      anchors.right: parent.right
      anchors.top: parent.top
      width: 600
      height: 500
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
            source: {index == -1 ? '' : "image://imageProvider/" + index}
            smooth: true
            visible: true
            cache: true
          }
        }
      }
    }
}
