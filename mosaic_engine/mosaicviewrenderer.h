#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <memory>


class MoMosaicModel;
class QQuickWindow;


class MoMosaicViewRenderer :
        public QQuickFramebufferObject::Renderer,
        protected QOpenGLFunctions
{
public:
    MoMosaicViewRenderer();
    ~MoMosaicViewRenderer();

    void render() Q_DECL_OVERRIDE;
    void synchronize(QQuickFramebufferObject* item) Q_DECL_OVERRIDE;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);


public slots:
    void setShowOutlines(bool yesNo);
    bool showOutlines() const;

private:
    bool showOutlines_;
    std::unique_ptr<QOpenGLShaderProgram> program_;
    std::shared_ptr<MoMosaicModel> model_;
    QSize viewportSize_;
    QQuickWindow *window_;

    void initGL();
    void initShaders();
    QString vshaderFileName() const;
    QString fshaderFileName() const;
};

#endif // MOMOSAICVIEWRENDERER_H
