#include "mosaicviewrenderer.h"

MoMosaicViewRenderer::MoMosaicViewRenderer(QObject *parent) : QObject(parent) {
}

void MoMosaicViewRenderer::paint() {
    if (!shader) {
        initializeOpenGLFunctions();
    }
}
