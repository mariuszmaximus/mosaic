TEMPLATE = app
CONFIG += testcase
SOURCES = foo_test.cpp
INCLUDEPATH += ../../thirdparty/googletest-release-1.7.0/include
LIBS += -L$$OUT_PWD/../../thirdparty/googletest-release-1.7.0/ -lgtest

