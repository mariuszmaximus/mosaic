import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import MoMosaic 1.0


ApplicationWindow {
    id: mainWindow
    width: 900
    height: 650

    property var targetURL


    ColumnLayout {
        spacing: 10
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 10
            topMargin: 10
        }
        Button {
            text: qsTr("Select Target")
            onClicked: targetFileDialog.open();
        }
        Button {
            text: qsTr("Add Mosaic Images")
            onClicked: mosaicFileDialog.open();
        }
    }

    JPEGFileChooser {
        id: targetFileDialog
        title: "Select target image"
        selectMultiple: false
        onAccepted: {
            mainWindow.targetURL = targetFileDialog.fileUrl
        }
    }

    JPEGFileChooser {
        id: mosaicFileDialog
        title: "Select additional mosaic images"
        selectMultiple: true
        onAccepted: {
            mosaicImages.imagesAdded(mosaicFileDialog.fileUrls)
        }
    }

    MosaicFlippable {
        width: 700
        height: 600
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 10
            topMargin: 10
        }
    }
}

