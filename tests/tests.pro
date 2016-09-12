TEMPLATE = subdirs
SUBDIRS += test_utilities
SUBDIRS += lennardjones_test
SUBDIRS += mosaicevolution_test
SUBDIRS += mosaicmodel_test
SUBDIRS += mosaicview_test
SUBDIRS += targetimage_test
SUBDIRS += quadrature_test

lennardjones_test.depends = test_utilities
mosaicevolution_test.depends = test_utilities
mosaicmodel_test.depends = test_utilities
mosaicview_test.depends = test_utilities
targetimage_test.depends = test_utilities
quadrature_test.depends = test_utilities

RUN_OPENGL_TESTS=$$(RUN_OPENGL_TESTS)
equals(RUN_OPENGL_TESTS, "true") {
  SUBDIRS += mosaicviewrenderer_test
}
