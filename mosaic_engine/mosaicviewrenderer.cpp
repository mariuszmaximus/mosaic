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

    xH_.resize(model_.size() * 6);
    yH_.resize(model_.size() * 6);
    zH_.resize(model_.size() * 6);
    widths_.resize(model_.size());
    heights_.resize(model_.size());
    model_.getWidths(&widths_[0]);
    model_.getHeights(&heights_[0]);

    const float* x = model_.getXCoords();
    const float* y = model_.getYCoords();

    for (int i = 0; i < model_.size(); ++i) {
        xH_[i * 6 + 0] = x[i] -0.5f * widths_[i];
        xH_[i * 6 + 1] = x[i] +0.5f * widths_[i];
        xH_[i * 6 + 2] = x[i] +0.5f * widths_[i];
        xH_[i * 6 + 3] = x[i] +0.5f * widths_[i];
        xH_[i * 6 + 4] = x[i] -0.5f * widths_[i];
        xH_[i * 6 + 5] = x[i] -0.5f * widths_[i];

        yH_[i * 6 + 0] = y[i] -0.5f * heights_[i];
        yH_[i * 6 + 1] = y[i] -0.5f * heights_[i];
        yH_[i * 6 + 2] = y[i] +0.5f * heights_[i];
        yH_[i * 6 + 3] = y[i] +0.5f * heights_[i];
        yH_[i * 6 + 4] = y[i] +0.5f * heights_[i];
        yH_[i * 6 + 5] = y[i] -0.5f * heights_[i];

        zH_[i * 6 + 0] = i;
        zH_[i * 6 + 1] = i;
        zH_[i * 6 + 2] = i;
        zH_[i * 6 + 3] = i;
        zH_[i * 6 + 4] = i;
        zH_[i * 6 + 5] = i;
    }

    program_->bind();
    program_->enableAttributeArray(xD_);
    program_->enableAttributeArray(yD_);
    program_->enableAttributeArray(zD_);
    program_->setAttributeArray(xD_, &xH_[0], 1);
    program_->setAttributeArray(yD_, &yH_[0], 1);
    program_->setAttributeArray(zD_, &zH_[0], 1);
    // TODO: should be using Triangle fans here.
    glDrawArrays(GL_TRIANGLES, 0, 6 * model_.size());
    GLenum err = glGetError();
    qDebug() << err;
    program_->disableAttributeArray(zD_);
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
    zD_ = program_->attributeLocation("z");
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
