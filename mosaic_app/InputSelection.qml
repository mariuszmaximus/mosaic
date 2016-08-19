import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0


Item {
    RowLayout {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 10
        ColumnLayout {
            id: buttons
            spacing: 10
            Button {
                text: qsTr("Select Target")
                onClicked: targetFileDialog.open();
            }
            Button {
                text: qsTr("Add Mosaic Images")
                onClicked: mosaicFileDialog.open();
            }
        }
        MosaicFlippable {
            width: 300
            height: 300
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: mosaicSourceThumbnails
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
            sourceImages.imagesAdded(mosaicFileDialog.fileUrls)
        }
    }
}
