TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += thirdparty
SUBDIRS += mosaic_engine
SUBDIRS += mosaic_app
SUBDIRS += tests

mosaic_app.depends = mosaic_engine
mosaic_app.tests = mosaic_engine
