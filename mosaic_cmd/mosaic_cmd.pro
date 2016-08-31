QT += qml

CONFIG += c++11

INCLUDEPATH += $$PWD/../mosaic_engine


SOURCES += main.cpp

LIBS += -L$$OUT_PWD/../mosaic_engine -lmosaic_engine
QMAKE_RPATHDIR += $$OUT_PWD/../mosaic_engine
