QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    sourceimages.cpp \
    thumbnail.cpp \
    imageprovider.cpp

RESOURCES += qml.qrc

INCLUDEPATH += ${PWD}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    sourceimages.h \
    thumbnail.h \
    imageprovider.h
