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
    void initShaders();

private:
    bool initialized;
    QOpenGLShaderProgram program;
};

#endif // MOMOSAICVIEWRENDERER_H
