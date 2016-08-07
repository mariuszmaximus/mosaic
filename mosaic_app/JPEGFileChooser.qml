import QtQuick 2.7
import QtQuick.Dialogs 1.2

FileDialog {
    nameFilters: ["JPEG Images (*.jpg, *.jpeg, *.JPG, *.JPEG)"]
    selectExisting: true
    selectFolder: false
    folder: shortcuts.pictures
}
