TEMPLATE = subdirs
SUBDIRS += test_utilities
SUBDIRS += mosaicevolution_test
SUBDIRS += mosaicmodel_test
SUBDIRS += mosaicview_test
SUBDIRS += targetimage_test

RUN_OPENGL_TESTS=$$(RUN_OPENGL_TESTS)
equals(RUN_OPENGL_TESTS, "true") {
  SUBDIRS += mosaicviewrenderer_test
}
