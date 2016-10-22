TEMPLATE = subdirs
SUBDIRS += test_utilities
SUBDIRS += badnesscomposite_test
SUBDIRS += lennardjones_test
SUBDIRS += mosaicevolution_test
SUBDIRS += mosaicmodel_test
SUBDIRS += mosaicview_test
SUBDIRS += targetimage_test
SUBDIRS += quadrature_test
SUBDIRS += imageutility_test
SUBDIRS += interactiontiletile_test
SUBDIRS += interactiontileborder_test
SUBDIRS += mosaictargetcorrelation_test

badnesscomposite_test.depends = test_utilities
lennardjones_test.depends = test_utilities
mosaicevolution_test.depends = test_utilities
mosaicmodel_test.depends = test_utilities
mosaicview_test.depends = test_utilities
targetimage_test.depends = test_utilities
quadrature_test.depends = test_utilities
imageutility_test.depends = test_utilities
interactiontiletile_test.depends = test_utilities
interactiontileborder_test.depends = test_utilities
mosaictargetcorrelation_test.depends = test_utilities

RUN_OPENGL_TESTS=$$(RUN_OPENGL_TESTS)
equals(RUN_OPENGL_TESTS, "true") {
  SUBDIRS += mosaicviewrenderer_test
}
