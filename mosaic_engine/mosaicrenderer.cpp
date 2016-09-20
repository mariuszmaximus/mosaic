#include "mosaicrenderer.h"

#include <limits>

#include <QQuickWindow>
#include <QOpenGLFramebufferObjectFormat>
#include <mosaicview.h>
#include <utilities.h>


MoMosaicRenderer::MoMosaicRenderer() :
    showOutlines_(true),
    showTargetImage_(false),
    xBuffer_(QOpenGLBuffer::VertexBuffer),
    yBuffer_(QOpenGLBuffer::VertexBuffer),
    widthBuffer_(QOpenGLBuffer::VertexBuffer),
    heightBuffer_(QOpenGLBuffer::VertexBuffer),
    rotationBuffer_(QOpenGLBuffer::VertexBuffer),
    currentBufferSize_(0),
    targetImage_(QOpenGLTexture::Target2D),
    vaoInitialized_(false)
{
}

MoMosaicRenderer::~MoMosaicRenderer() {
    xBuffer_.destroy();
    yBuffer_.destroy();
    widthBuffer_.destroy();
    heightBuffer_.destroy();
    rotationBuffer_.destroy();
}

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    MO_CHECK_GL_ERROR;

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    if (showTargetImage_) {
        renderTargetImage();
    }

    renderMosaicTiles();
}

void MoMosaicRenderer::renderMosaicTiles() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    MO_CHECK_GL_ERROR;

    ensureVAOIsSetUp();
    MO_CHECK_GL_ERROR;

    ensureBuffersAreLargeEnough(model_.size());
    MO_CHECK_GL_ERROR;

    float* xH_ = model_.getXCoords();
    float* yH_ = model_.getYCoords();
    for (int i = 0; i < model_.size(); ++i) {
        xH_[i] = 300.0f * (i - 0.5);
        yH_[i] = 200.0f * (i - 0.5);
    }
    widthsH_.resize(model_.size());
    model_.getWidths(&widthsH_[0]);
    heightsH_.resize(model_.size());
    model_.getHeights(&heightsH_[0]);
    float* rotationsH_ = model_.getRotations();

    xBuffer_.bind();
    xBuffer_.write(0, xH_, model_.size() * sizeof(float));
    xBuffer_.release();
    MO_CHECK_GL_ERROR;

    yBuffer_.bind();
    yBuffer_.write(0, yH_, model_.size() * sizeof(float));
    yBuffer_.release();
    MO_CHECK_GL_ERROR;

    widthBuffer_.bind();
    widthBuffer_.write(0, &widthsH_[0], model_.size() * sizeof(float));
    widthBuffer_.release();
    MO_CHECK_GL_ERROR;

    heightBuffer_.bind();
    heightBuffer_.write(0, &heightsH_[0], model_.size() * sizeof(float));
    heightBuffer_.release();
    MO_CHECK_GL_ERROR;

    rotationBuffer_.bind();
    rotationBuffer_.write(0, rotationsH_, model_.size() * sizeof(float));
    rotationBuffer_.release();
    MO_CHECK_GL_ERROR;

    program_->bind();
    MO_CHECK_GL_ERROR;

    program_->setUniformValue("targetWidth", targetWidth_);
    program_->setUniformValue("targetHeight", targetHeight_);
    program_->setUniformValue("numTiles", (float)model_.size());
    MO_CHECK_GL_ERROR;

    vao_.bind();
    MO_CHECK_GL_ERROR;

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, model_.size());
    MO_CHECK_GL_ERROR;

    vao_.release();
    program_->release();
    MO_CHECK_GL_ERROR;

    if (window_) {
        window_->resetOpenGLState();
    }
}

void MoMosaicRenderer::synchronize(QQuickFramebufferObject *item) {
    MoMosaicView* mosaicView = static_cast<MoMosaicView*>(item);
    model_ = *mosaicView->getModel();
    targetWidth_ = mosaicView->width();
    targetHeight_ = mosaicView->height();

    const MoTargetImage& img = model_.getTargetImage();
    if (!targetImage_.isCreated() && !img.getImage().isNull()) {
        qDebug() << "Setting texture";
        targetImage_.setData(img.getImage(),
                             QOpenGLTexture::DontGenerateMipMaps);
        targetImage_.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        targetImage_.setMagnificationFilter(QOpenGLTexture::Linear);
    }
}

void MoMosaicRenderer::initGL() {
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;
        initializeOpenGLFunctions();
    }
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

    targetImageShader_.reset(new QOpenGLShaderProgram);
    if (!targetImageShader_->addShaderFromSourceFile(QOpenGLShader::Vertex,
        ":/shaders/vshader_target_image.glsl")) {
        throw std::runtime_error(
                    "Failed to add vertex shader for target image shader.");
    }
    if (!targetImageShader_->addShaderFromSourceFile(QOpenGLShader::Fragment,
        ":/shaders/fshader_target_image.glsl")) {
        throw std::runtime_error(
                    "Failed to add fragment shader for target image shader.");
    }
    if (!targetImageShader_->link()) {
        throw std::runtime_error("Failed to link target image shader.");
    }
    if (!targetImageShader_->bind()) {
        throw std::runtime_error("Failed to bind target image shader.");
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

bool MoMosaicRenderer::getShowOutlines() const {
    return showOutlines_;
}

void MoMosaicRenderer::setShowTargetImage(bool yesNo) {
    showTargetImage_ = yesNo;
}

bool MoMosaicRenderer::getShowTargetImage() const {
    return showTargetImage_;
}

void MoMosaicRenderer::ensureBuffersAreLargeEnough(size_t size) {
    size_t requiredSize = size * sizeof(float);
    if (requiredSize > std::numeric_limits<int>::max()) {
        throw std::runtime_error("Required buffer size too large.");
    }
    int iRequiredSize = static_cast<int>(requiredSize);
    if (currentBufferSize_ < iRequiredSize) {
        xBuffer_.bind();
        xBuffer_.allocate(iRequiredSize);
        xBuffer_.release();

        yBuffer_.bind();
        yBuffer_.allocate(iRequiredSize);
        yBuffer_.release();

        widthBuffer_.bind();
        widthBuffer_.allocate(iRequiredSize);
        widthBuffer_.release();

        heightBuffer_.bind();
        heightBuffer_.allocate(iRequiredSize);
        heightBuffer_.release();

        rotationBuffer_.bind();
        rotationBuffer_.allocate(iRequiredSize);
        rotationBuffer_.release();

        currentBufferSize_ = iRequiredSize;
    }
}

void MoMosaicRenderer::setVertexAttribDivisor(int loc, int value) {
    if (loc == -1) {
        throw std::runtime_error("Failed to find attribute location in shader program");
    }
    glVertexAttribDivisor(loc, value);
}

void MoMosaicRenderer::ensureVAOIsSetUp() {
    if (vaoInitialized_) return;
    // Create shaders
    initShaders();
    program_->bind();

    // Set up buffers
    bool err = true;
    err &= xBuffer_.create();
    err &= yBuffer_.create();
    err &= widthBuffer_.create();
    err &= heightBuffer_.create();
    err &= rotationBuffer_.create();
    if (!err) {
        throw std::runtime_error("Failed to allocated vertex buffers.");
    }

    xBuffer_.bind();
    xBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    xBuffer_.release();
    MO_CHECK_GL_ERROR;

    yBuffer_.bind();
    yBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    yBuffer_.release();
    MO_CHECK_GL_ERROR;

    widthBuffer_.bind();
    widthBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    widthBuffer_.release();
    MO_CHECK_GL_ERROR;

    heightBuffer_.bind();
    heightBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    heightBuffer_.release();
    MO_CHECK_GL_ERROR;

    rotationBuffer_.bind();
    rotationBuffer_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    rotationBuffer_.release();
    MO_CHECK_GL_ERROR;

    // Create vertex array object
    vao_.create();
    vao_.bind();
    MO_CHECK_GL_ERROR;

    program_->enableAttributeArray("x");
    program_->enableAttributeArray("y");
    program_->enableAttributeArray("width");
    program_->enableAttributeArray("height");
    program_->enableAttributeArray("rotation");
    MO_CHECK_GL_ERROR;

    xBuffer_.bind();
    program_->setAttributeBuffer("x", GL_FLOAT, 0, 1);
    setVertexAttribDivisor(program_->attributeLocation("x"), 1);
    xBuffer_.release();
    MO_CHECK_GL_ERROR;

    yBuffer_.bind();
    program_->setAttributeBuffer("y", GL_FLOAT, 0, 1);
    setVertexAttribDivisor(program_->attributeLocation("y"), 1);
    yBuffer_.release();
    MO_CHECK_GL_ERROR;

    widthBuffer_.bind();
    program_->setAttributeBuffer("width", GL_FLOAT, 0, 1);
    setVertexAttribDivisor(program_->attributeLocation("width"), 1);
    widthBuffer_.release();
    MO_CHECK_GL_ERROR;

    heightBuffer_.bind();
    program_->setAttributeBuffer("height", GL_FLOAT, 0, 1);
    setVertexAttribDivisor(program_->attributeLocation("height"), 1);
    heightBuffer_.release();
    MO_CHECK_GL_ERROR;

    rotationBuffer_.bind();
    program_->setAttributeBuffer("rotation", GL_FLOAT, 0, 1);
    setVertexAttribDivisor(program_->attributeLocation("rotation"), 1);
    rotationBuffer_.release();
    MO_CHECK_GL_ERROR;

    vao_.release();
    program_->release();
    MO_CHECK_GL_ERROR;

    vaoInitialized_ = true;
}

void MoMosaicRenderer::renderTargetImage() {
    if (targetImageShader_) {
    qDebug() << "In MoMosaicRenderer::renderTargetImage()";
        targetImageShader_->bind();
        targetImage_.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        targetImage_.release();
        targetImageShader_->release();
    }
}

void MoMosaicRenderer::setModel(std::shared_ptr<MoMosaicModel> model) {
    model_ = *model;
}

MoMosaicModel MoMosaicRenderer::getModel() const {
    return model_;
}

void MoMosaicRenderer::setWindow(QQuickWindow *win) {
    window_ = win;
}
