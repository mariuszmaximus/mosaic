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
        initShaders();
    }
}

void MoMosaicViewRenderer::initShaders() {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl")) {
        throw std::runtime_error("Failed to add vertex shader.");
    }
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl")) {
        throw std::runtime_error("Failed to add fragment shader.");
    }
    if (!program.link()) {
        throw std::runtime_error("Failed to link shader.");
    }
    if (!program.bind()) {
        throw std::runtime_error("Failed to bind shader.");
    }
}
