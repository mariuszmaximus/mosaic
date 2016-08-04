QT += quick
TEMPLATE = lib
TARGET = mosaic_engine

include(../compiler_config.pri)

SOURCES = foo.cpp \
    mosaicview.cpp \
    mosaicviewrenderer.cpp
HEADERS = foo.h \
    mosaicview.h \
    mosaicviewrenderer.h
