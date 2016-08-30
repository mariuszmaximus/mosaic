#include "mosaicviewrenderer.h"

#include <QQuickWindow>
#include <QOpenGLFramebufferObjectFormat>
#include <mosaicview.h>


MoMosaicViewRenderer::MoMosaicViewRenderer() :
    showOutlines_(true) {
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

    const float* xH_ = model_.getXCoords();
    const float* yH_ = model_.getYCoords();
    widthsH_.resize(model_.size());
    model_.getWidths(&widthsH_[0]);
    heightsH_.resize(model_.size());
    model_.getHeights(&heightsH_[0]);

    program_->bind();

    int targetWidth = program_->uniformLocation("targetWidth");
    glUniform1f(targetWidth, 1000.0f);

    int targetHeight = program_->uniformLocation("targetHeight");
    glUniform1f(targetHeight, 1000.0f);

    program_->enableAttributeArray(xD_);
    program_->setAttributeArray(xD_, &xH_[0], 1);

    program_->enableAttributeArray(yD_);
    program_->setAttributeArray(yD_, &yH_[0], 1);

    program_->enableAttributeArray(widthsD_);
    program_->setAttributeArray(widthsD_, &widthsH_[0], 1);

    program_->enableAttributeArray(heightsD_);
    program_->setAttributeArray(heightsD_, &heightsH_[0], 1);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, model_.size());
    GLenum err = glGetError();
    qDebug() << err;

    program_->enableAttributeArray(heightsD_);
    program_->enableAttributeArray(widthsD_);
    program_->disableAttributeArray(yD_);
    program_->disableAttributeArray(xD_);
    program_->release();


    if (window_) {
        window_->resetOpenGLState();
    }
}

void MoMosaicViewRenderer::synchronize(QQuickFramebufferObject *item) {
    MoMosaicView* mosaicView = static_cast<MoMosaicView*>(item);
    model_ = *mosaicView->getModel();
}

void MoMosaicViewRenderer::initGL() {
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;
        initializeOpenGLFunctions();
    }
    initShaders();
    xD_ = program_->attributeLocation("x");
    yD_ = program_->attributeLocation("y");
    widthsD_ = program_->attributeLocation("width");
    heightsD_ = program_->attributeLocation("height");
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
    model_ = *model;
}

MoMosaicModel MoMosaicViewRenderer::getModel() const {
    return model_;
}

void MoMosaicViewRenderer::setViewportSize(const QSize &size) {
    viewportSize_ = size;
}

void MoMosaicViewRenderer::setWindow(QQuickWindow *win) {
    window_ = win;
}
