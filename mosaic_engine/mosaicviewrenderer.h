#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QQuickFramebufferObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <mosaicmodel.h>

#include <memory>


class MoMosaicModel;
class QQuickWindow;


class MoMosaicViewRenderer :
        public QQuickFramebufferObject::Renderer,
        protected QOpenGLFunctions_3_3_Core
{
public:
    MoMosaicViewRenderer();
    ~MoMosaicViewRenderer();

    void render() Q_DECL_OVERRIDE;
    void synchronize(QQuickFramebufferObject* item) Q_DECL_OVERRIDE;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    void setModel(std::shared_ptr<MoMosaicModel> model);
    MoMosaicModel getModel() const;
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);


public slots:
    void setShowOutlines(bool yesNo);
    bool showOutlines() const;

private:
    bool showOutlines_;
    std::unique_ptr<QOpenGLShaderProgram> program_;
    QSize viewportSize_;
    QQuickWindow *window_;

    MoMosaicModel model_;

    std::vector<float> widthsH_;
    std::vector<float> heightsH_;

    int xD_;
    int yD_;
    int widthsD_;
    int heightsD_;

    void initGL();
    void initShaders();
    QString vshaderFileName() const;
    QString fshaderFileName() const;
};

#endif // MOMOSAICVIEWRENDERER_H
