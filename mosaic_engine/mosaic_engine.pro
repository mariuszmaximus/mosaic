QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    mosaicview.cpp \
    mosaicviewrenderer.cpp \
    mosaicmodel.cpp
HEADERS = \
    mosaicview.h \
    mosaicviewrenderer.h \
    mosaicmodel.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
