#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QQuickImageProvider>
#include <memory>

class MoMosaicModel;
class MoMosaicViewRenderer;


class MoMosaicView : public QQuickImageProvider {
public:
    MoMosaicView();
    ~MoMosaicView();
    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;

signals:

public slots:

private slots:

private:
    bool initialized;
    MoMosaicViewRenderer* renderer_;

    void initGL();

    Q_DISABLE_COPY(MoMosaicView)
};

#endif // MOSAICVIEW_H
