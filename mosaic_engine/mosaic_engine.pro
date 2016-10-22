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
    tiletextures.cpp \
    interactiontiletile.cpp \
    potentiallennardjones.cpp \
    interactiontileborder.cpp \
    interactionhelpers.cpp \
    badnesscomposite.cpp \
    mosaicupdateoptimize.cpp \
    imageutilities.cpp \
    mosaictargetcorrelation.cpp
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
    tiletextures.h \
    badness.h \
    interactiontiletile.h \
    potential.h \
    potentiallennardjones.h \
    interactiontileborder.h \
    interactionhelpers.h \
    badnesscomposite.h \
    mosaicupdateoptimize.h \
    imageutilities.h \
    mosaictargetcorrelation.h

DISTFILES +=

RESOURCES += \
    engine_resources.qrc
