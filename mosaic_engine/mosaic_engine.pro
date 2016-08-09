QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    mosaicviewrenderer.cpp \
    mosaicmodel.cpp \
    mosaicimageprovider.cpp
HEADERS = \
    mosaicviewrenderer.h \
    mosaicmodel.h \
    mosaicimageprovider.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
