QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    maindriver.cpp \
    mosaicview.cpp \
    mosaicviewrenderer.cpp \
    mosaicmodel.cpp \
    mosaicevolution.cpp \
    mosaicupdate.cpp \
    sourceimages.cpp \
    tile.cpp \
    targetimage.cpp \
    thumbnail.cpp \
    evolutionrunner.cpp
HEADERS = \
    maindriver.h \
    mosaicview.h \
    mosaicviewrenderer.h \
    mosaicmodel.h \
    mosaicevolution.h \
    mosaicupdate.h \
    sourceimages.h \
    tile.h \
    targetimage.h \
    thumbnail.h \
    evolutionrunner.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
