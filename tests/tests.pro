TEMPLATE = subdirs
SUBDIRS += mosaicevolution_test
SUBDIRS += mosaicmodel_test
SUBDIRS += mosaicview_test
SUBDIRS += targetimage_test

HAVE_OPENGL=$$(HAVE_OPENGL)
equals(HAVE_OPENGL, "true") {
  SUBDIRS += mosaicviewrenderer_test
}
