QT += quick
TEMPLATE = app
CONFIG += testcase
include(../compiler_config.pri)

INCLUDEPATH += \
    ../../thirdparty/googletest-release-1.7.0/include \
    ../../mosaic_engine \
    ../test_utilities
LIBS += -L$$OUT_PWD/../../thirdparty/googletest-release-1.7.0/ -lgtest
LIBS += -L$$OUT_PWD/../../mosaic_engine -lmosaic_engine
LIBS += -L$$OUT_PWD/../test_utilities -ltest_utilities
QMAKE_RPATHDIR += $$OUT_PWD/../../thirdparty/googletest-release-1.7.0/
QMAKE_RPATHDIR += $$OUT_PWD/../../mosaic_engine

