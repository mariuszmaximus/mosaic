import QtQuick 2.7
import QtQuick.Dialogs 1.0

Page1Form {
    masterImage.onClicked: {
        masterFileDialog.open();
    }
    mosaicImages.onClicked: {
        mosaicFileDialog.open();
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
}
