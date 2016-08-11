#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QQuickImageProvider>
#include <memory>

class MoMosaicModel;
class MoMosaicViewRenderer;


class MoMosaicImageProvider : public QQuickImageProvider {
public:
    MoMosaicImageProvider();
    ~MoMosaicImageProvider();
    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;

signals:

public slots:

private slots:

private:
    bool initialized;
    MoMosaicViewRenderer* renderer_;

    void initGL();

    Q_DISABLE_COPY(MoMosaicImageProvider)
};

#endif // MOSAICVIEW_H
