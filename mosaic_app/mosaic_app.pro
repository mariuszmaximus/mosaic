QT += qml quick

CONFIG += c++11

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../mosaic_engine


include(../compiler_config.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    imageprovider.h

SOURCES += main.cpp \
    imageprovider.cpp

LIBS += -L$$OUT_PWD/../mosaic_engine -lmosaic_engine
QMAKE_RPATHDIR += $$OUT_PWD/../mosaic_engine
