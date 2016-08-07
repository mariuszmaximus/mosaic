#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QtQuick/QQuickItem>
#include <memory>

class MoMosaicModel;
class MoMosaicViewRenderer;


class MoMosaicView : public QQuickItem {
    Q_OBJECT
public:
    MoMosaicView();
    ~MoMosaicView();
    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;

signals:

public slots:
private:
    bool initialized;
    MoMosaicViewRenderer* renderer_;

    void initGL();

    Q_DISABLE_COPY(MoMosaicView)
};

#endif // MOSAICVIEW_H
