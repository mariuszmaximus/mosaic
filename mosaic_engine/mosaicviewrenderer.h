#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <memory>


class MoMosaicModel;


class MoMosaicViewRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MoMosaicViewRenderer(QObject *parent = 0);

    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;

signals:

public slots:
    void paint();
    void setShowOutlines(bool yesNo);
    bool showOutlines() const;

private:
    bool showOutlines_;
    std::unique_ptr<QOpenGLShaderProgram> program_;
    std::shared_ptr<MoMosaicModel> model_;

    void initGL();
    void initShaders();
    QString vshaderFileName() const;
    QString fshaderFileName() const;
};

#endif // MOMOSAICVIEWRENDERER_H
