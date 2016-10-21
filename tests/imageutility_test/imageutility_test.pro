include($$PWD/../test_case.pri)
SOURCES = \
    imageutility_test.cpp \
    gaussianblur_test.cpp \
    distancebetweenimages_test.cpp

TEST_MASTERS = \
    IsZeroIfImageComesFromFile_master.png

# TODO: Would be nice to turn this into a macro.
for(FILE,TEST_MASTERS){
    QMAKE_POST_LINK += $$quote(cp $${FILE} $${DESTDIR}$$escape_expand(\n\t))
}
