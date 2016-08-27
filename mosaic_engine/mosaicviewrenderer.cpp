#include "mosaicviewrenderer.h"

#include <QQuickWindow>
#include <QOpenGLFramebufferObjectFormat>
#include <mosaicview.h>


MoMosaicViewRenderer::MoMosaicViewRenderer() :
    showOutlines_(false) {
}

MoMosaicViewRenderer::~MoMosaicViewRenderer() {}

QOpenGLFramebufferObject* MoMosaicViewRenderer::createFramebufferObject(
        const QSize &size){
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

void MoMosaicViewRenderer::render() {
    static long int i = 0;
    if (i == 0) {
        initGL();
    }
    ++i;

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    if (window_) {
        window_->resetOpenGLState();
    }
}

void MoMosaicViewRenderer::synchronize(QQuickFramebufferObject *item) {
    MoMosaicView* mosaicView = static_cast<MoMosaicView*>(item);
    std::shared_ptr<MoMosaicModel> model = mosaicView->getModel();

}

void MoMosaicViewRenderer::initGL() {
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;
        initializeOpenGLFunctions();
    }

    initShaders();
}

void MoMosaicViewRenderer::initShaders() {
    program_.reset(new QOpenGLShaderProgram);
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           vshaderFileName())) {
        throw std::runtime_error("Failed to add vertex shader.");
    }
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           fshaderFileName())) {
        throw std::runtime_error("Failed to add fragment shader.");
    }
    if (!program_->link()) {
        throw std::runtime_error("Failed to link shader.");
    }
    if (!program_->bind()) {
        throw std::runtime_error("Failed to bind shader.");
    }
}

QString MoMosaicViewRenderer::vshaderFileName() const {
    if (showOutlines_) {
        return ":/shaders/vshader_outline.glsl";
    } else {
        return ":/shaders/vshader.glsl";
    }
}

QString MoMosaicViewRenderer::fshaderFileName() const {
    if (showOutlines_) {
        return ":/shaders/fshader_outline.glsl";
    } else {
        return ":/shaders/fshader.glsl";

    }
}

void MoMosaicViewRenderer::setShowOutlines(bool yesNo) {
    if (showOutlines_ == yesNo) return;
    showOutlines_ = yesNo;
    initShaders();
}

bool MoMosaicViewRenderer::showOutlines() const {
    return showOutlines_;
}

void MoMosaicViewRenderer::setModel(std::shared_ptr<MoMosaicModel> model) {
    model_ = model;
}

std::shared_ptr<MoMosaicModel> MoMosaicViewRenderer::getModel() const {
    return model_;
}

void MoMosaicViewRenderer::setViewportSize(const QSize &size) {
    viewportSize_ = size;
}

void MoMosaicViewRenderer::setWindow(QQuickWindow *win) {
    window_ = win;
}
