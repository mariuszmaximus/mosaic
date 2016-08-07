import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import MoMosaic 1.0


ApplicationWindow {
    id: mainWindow
    width: 900
    height: 600

    property var targetURL


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


    FileDialog {
        id: targetFileDialog
        title: "Select the mosaic target image"
        nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        folder: shortcuts.pictures
        onAccepted: {
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
            mosaicImages.imagesAdded(mosaicFileDialog.fileUrls)
        }
    }

    MosaicFlippable {
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
    }
}
