QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    mosaicview.cpp \
    mosaicviewrenderer.cpp \
    mosaicmodel.cpp \
    mosaicevolution.cpp \
    mosaicupdate.cpp
HEADERS = \
    mosaicview.h \
    mosaicviewrenderer.h \
    mosaicmodel.h \
    mosaicevolution.h \
    mosaicupdate.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
