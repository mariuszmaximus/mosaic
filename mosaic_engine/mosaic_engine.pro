QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    mosaicview.cpp \
    mosaicviewrenderer.cpp
HEADERS = \
    mosaicview.h \
    mosaicviewrenderer.h

DISTFILES += \
    vshader.vert \
    fshader.frag

RESOURCES += \
    engine_resources.qrc
