TEMPLATE = lib
TARGET = gtest
INCLUDEPATH += include
INCLUDEPATH += $$(PWD)

DEFINES += "GTEST_HAS_PTHREAD=0"
DEFINES += "GTEST_CREATE_SHARED_LIBRARY=1"

SOURCES = \
    src/gtest-all.cc \
    src/gtest_main.cc
