QT += quick
TEMPLATE = lib
TARGET = test_utilities

include(../../compiler_config.pri)
INCLUDEPATH += \
    ../../mosaic_engine

SOURCES = \
    test_utilities.cpp
HEADERS = \
    test_utilities.h
