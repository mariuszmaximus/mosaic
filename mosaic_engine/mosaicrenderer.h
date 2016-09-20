#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QQuickFramebufferObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <mosaicmodel.h>

#include <memory>


class MoMosaicModel;
class QQuickWindow;


class MoMosaicRenderer :
        public QQuickFramebufferObject::Renderer,
        protected QOpenGLFunctions_3_3_Core
{
public:
    MoMosaicRenderer();
    ~MoMosaicRenderer();

    void render() Q_DECL_OVERRIDE;
    void synchronize(QQuickFramebufferObject* item) Q_DECL_OVERRIDE;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    void setModel(std::shared_ptr<MoMosaicModel> model);
    MoMosaicModel getModel() const;
    void setWindow(QQuickWindow *window);

    void setShowOutlines(bool yesNo);
    bool getShowOutlines() const;
    void setShowTargetImage(bool yesNo);
    bool getShowTargetImage() const;

private:
    bool showOutlines_;
    bool showTargetImage_;
    std::unique_ptr<QOpenGLShaderProgram> program_;
    std::unique_ptr<QOpenGLShaderProgram> targetImageShader_;
    QQuickWindow *window_;
    float targetWidth_;
    float targetHeight_;

    MoMosaicModel model_;

    std::vector<float> widthsH_;
    std::vector<float> heightsH_;

    QOpenGLVertexArrayObject vao_;
    QOpenGLBuffer xBuffer_;
    QOpenGLBuffer yBuffer_;
    QOpenGLBuffer widthBuffer_;
    QOpenGLBuffer heightBuffer_;
    QOpenGLBuffer rotationBuffer_;
    int currentBufferSize_;

    QOpenGLTexture targetImage_;

    void ensureBuffersAreLargeEnough(size_t size);
    bool vaoInitialized_;
    void ensureVAOIsSetUp();

    void renderTargetImage();
    void renderMosaicTiles();

    void initGL();
    void initShaders();
    QString vshaderFileName() const;
    QString fshaderFileName() const;
    void setVertexAttribDivisor(int loc, int value);
};

#endif // MOMOSAICVIEWRENDERER_H
