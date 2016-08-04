#include "mosaicviewrenderer.h"

MoMosaicViewRenderer::MoMosaicViewRenderer(QObject *parent) :
    QObject(parent), initialized(false) {
}

void MoMosaicViewRenderer::paint() {
    if (!initialized) {
        initGL();
    }
}

void MoMosaicViewRenderer::initGL() {
    if (!initialized) {
        initialized = true;
        initializeOpenGLFunctions();
    }
}
