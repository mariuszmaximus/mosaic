import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias masterImage: masterImage
    property alias mosaicImages: mosaicImages

    RowLayout {
        anchors.centerIn: parent

        Button {
            id: masterImage
            text: qsTr("Select master Image")
        }

        Button {
            id: mosaicImages
            text: qsTr("Add mosaic images")
        }
    }
}
