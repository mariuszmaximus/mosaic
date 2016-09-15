#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QtQuick/QQuickFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <memory>

class MoMosaicModel;
class MoMosaicRenderer;


class MoMosaicView : public QQuickFramebufferObject {
    Q_OBJECT
    Q_PROPERTY(bool showOutlines MEMBER showOutlines_ READ getShowOutlines WRITE setShowOutlines)
    Q_PROPERTY(bool showTargetImage MEMBER showTargetImage_ READ getShowTargetImage WRITE setShowTargetImage)
public:
    MoMosaicView();
    ~MoMosaicView();
    std::shared_ptr<MoMosaicModel> getModel() const;

    QQuickFramebufferObject::Renderer* createRenderer() const;

    void setShowOutlines(bool yesNo);
    bool getShowOutlines() const;
    void setShowTargetImage(bool yesNo);
    bool getShowTargetImage() const;

signals:

public slots:
    void setModel(std::shared_ptr<MoMosaicModel> model);
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    bool initialized_;
    bool showOutlines_;
    bool showTargetImage_;
    std::unique_ptr<MoMosaicRenderer> renderer_;
    MoMosaicRenderer* getRenderer() const;

    void initGL();

    Q_DISABLE_COPY(MoMosaicView)
};

#endif // MOSAICVIEW_H
