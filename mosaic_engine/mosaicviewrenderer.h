#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <memory>


class MoMosaicViewRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MoMosaicViewRenderer(QObject *parent = 0);

signals:

public slots:
    void paint();
    void initGL();

private:
    bool initialized;
    std::shared_ptr<QOpenGLShaderProgram> shader;
};

#endif // MOMOSAICVIEWRENDERER_H
