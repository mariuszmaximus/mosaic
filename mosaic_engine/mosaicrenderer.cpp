#include "mosaicrenderer.h"

#include <limits>

#include <QQuickWindow>
#include <QOpenGLFramebufferObjectFormat>
#include <mosaicview.h>

#define CHECKED_CALL(call, message)            \
    do {                                       \
        if (!(call)) {                         \
            throw std::runtime_error(message); \
        }                                      \
    } while(0)



MoMosaicRenderer::MoMosaicRenderer() :
    showOutlines_(true),
    xBuffer_(QOpenGLBuffer::VertexBuffer),
    yBuffer_(QOpenGLBuffer::VertexBuffer),
    widthBuffer_(QOpenGLBuffer::VertexBuffer),
    heightBuffer_(QOpenGLBuffer::VertexBuffer)
{
}

MoMosaicRenderer::~MoMosaicRenderer() {}

QOpenGLFramebufferObject* MoMosaicRenderer::createFramebufferObject(
        const QSize &size){
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

void MoMosaicRenderer::render() {
    static long int i = 0;
    if (i == 0) {
        initGL();
    }
    ++i;

    glClearColor(0.1f, 0.1f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float* xH_ = model_.getXCoords();
    float* yH_ = model_.getYCoords();
    for (int i = 0; i < model_.size(); ++i) {
        xH_[i] += 100.0f * i;
        yH_[i] += 100.0f * i;
    }
    widthsH_.resize(model_.size());
    model_.getWidths(&widthsH_[0]);
    heightsH_.resize(model_.size());
    model_.getHeights(&heightsH_[0]);

    qDebug() << "model_.size() == " << model_.size();

    program_->bind();
    // TODO: I think we need a vertex array object here

    // Fill Buffers
    ensureBuffersHaveBeenCreated();
    ensureBuffersAreLargeEnough(model_.size());

    CHECKED_CALL(xBuffer_.bind(), "Failed to bind buffer");
    xBuffer_.write(0, xH_, model_.size() * sizeof(float));
    program_->enableAttributeArray("x");
    glVertexAttribPointer(xD_, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(xD_, 1);

    CHECKED_CALL(yBuffer_.bind(), "Failed to bind buffer");
    yBuffer_.write(0, yH_, model_.size() * sizeof(float));
    program_->enableAttributeArray("y");
    glVertexAttribPointer(yD_, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(yD_, 1);

    // TODO: can do these without copying by mapping
    CHECKED_CALL(widthBuffer_.bind(), "Failed to bind buffer");
    widthBuffer_.write(0, &widthsH_[0], model_.size() * sizeof(float));
    program_->enableAttributeArray("width");
    glVertexAttribPointer(widthsD_, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(widthsD_, 1);

    CHECKED_CALL(heightBuffer_.bind(), "Failed to bind buffer");
    heightBuffer_.write(0, &heightsH_[0], model_.size() * sizeof(float));
    program_->enableAttributeArray("height");
    glVertexAttribPointer(heightsD_, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(heightsD_, 1);
    program_->disableAttributeArray(heightsD_);

    program_->setUniformValue("targetWidth", 1000.0f);
    program_->setUniformValue("targetHeight", 1000.0f);
    program_->setUniformValue("numTiles", static_cast<int>(model_.size()));

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, model_.size());
    GLenum err = glGetError();
    qDebug() << " err == " << err;
    qDebug() << " GL_INVALID_OPERATION == " << GL_INVALID_OPERATION;

    program_->release();


    if (window_) {
        window_->resetOpenGLState();
    }
}

void MoMosaicRenderer::synchronize(QQuickFramebufferObject *item) {
    MoMosaicView* mosaicView = static_cast<MoMosaicView*>(item);
    model_ = *mosaicView->getModel();
}

void MoMosaicRenderer::initGL() {
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

void MoMosaicRenderer::initShaders() {
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

QString MoMosaicRenderer::vshaderFileName() const {
    if (showOutlines_) {
        return ":/shaders/vshader_outline.glsl";
    } else {
        return ":/shaders/vshader.glsl";
    }
}

QString MoMosaicRenderer::fshaderFileName() const {
    if (showOutlines_) {
        return ":/shaders/fshader_outline.glsl";
    } else {
        return ":/shaders/fshader.glsl";

    }
}

void MoMosaicRenderer::setShowOutlines(bool yesNo) {
    if (showOutlines_ == yesNo) return;
    showOutlines_ = yesNo;
    initShaders();
}

bool MoMosaicRenderer::showOutlines() const {
    return showOutlines_;
}

void MoMosaicRenderer::ensureBuffersHaveBeenCreated() {
    bool err = true;
    err &= xBuffer_.create();
    err &= yBuffer_.create();
    err &= widthBuffer_.create();
    err &= heightBuffer_.create();
    if (!err) {
        throw std::runtime_error("Failed to allocated vertex buffers.");
    }
    xBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    yBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    widthBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    heightBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
}

void MoMosaicRenderer::ensureBuffersAreLargeEnough(size_t size) {
    size_t requiredSize = size * sizeof(float);
    if (requiredSize > std::numeric_limits<int>::max()) {
        throw std::runtime_error("Required buffer size too large.");
    }
    int iRequiredSize = static_cast<int>(requiredSize);
    if (xBuffer_.size() < iRequiredSize) {
        xBuffer_.allocate(iRequiredSize);
    }
    if (yBuffer_.size() < iRequiredSize) {
        yBuffer_.allocate(iRequiredSize);
    }
    if (widthBuffer_.size() < iRequiredSize) {
        widthBuffer_.allocate(iRequiredSize);
    }
    if (heightBuffer_.size() < iRequiredSize) {
        heightBuffer_.allocate(iRequiredSize);
    }
}

void MoMosaicRenderer::setModel(std::shared_ptr<MoMosaicModel> model) {
    model_ = *model;
}

MoMosaicModel MoMosaicRenderer::getModel() const {
    return model_;
}

void MoMosaicRenderer::setViewportSize(const QSize &size) {
    viewportSize_ = size;
}

void MoMosaicRenderer::setWindow(QQuickWindow *win) {
    window_ = win;
}
