QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = \
    maindriver.cpp \
    mosaicview.cpp \
    mosaicmodel.cpp \
    mosaicevolution.cpp \
    mosaicupdate.cpp \
    sourceimages.cpp \
    tile.cpp \
    targetimage.cpp \
    thumbnail.cpp \
    evolutionrunner.cpp \
    mosaicupdatedelay.cpp \
    mosaicrenderer.cpp \
    lennardjones.cpp \
    tiletextures.cpp
HEADERS = \
    maindriver.h \
    mosaicview.h \
    mosaicmodel.h \
    mosaicevolution.h \
    mosaicupdate.h \
    sourceimages.h \
    tile.h \
    targetimage.h \
    thumbnail.h \
    evolutionrunner.h \
    mosaicupdatedelay.h \
    mosaicrenderer.h \
    utilities.h \
    quadraturerule.h \
    lennardjones.h \
    tiletextures.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
