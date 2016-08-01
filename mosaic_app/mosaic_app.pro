QT += qml quick

CONFIG += c++11

RESOURCES += qml.qrc

INCLUDEPATH += $$(PWD)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    maindriver.h \
    sourceimages.h \
    thumbnail.h \
    imageprovider.h

SOURCES += main.cpp \
    maindriver.cpp \
    sourceimages.cpp \
    thumbnail.cpp \
    imageprovider.cpp
