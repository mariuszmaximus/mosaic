#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QQuickImageProvider>
#include <QUrl>

#include <memory>

class MoMosaicModel;
class MoMosaicViewRenderer;


class MoMosaicImageProvider : public QQuickImageProvider {
public:
    MoMosaicImageProvider();
    ~MoMosaicImageProvider();
    void setModel(std::shared_ptr<MoMosaicModel> model);
    std::shared_ptr<MoMosaicModel> getModel() const;
    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize);
    QImage emptyImage(const QSize& size) const;

signals:

public slots:
    void setTargetImage(const QUrl& url);

private slots:

private:
    bool initialized;
    MoMosaicViewRenderer* renderer_;

    void initGL();

    Q_DISABLE_COPY(MoMosaicImageProvider)
};

#endif // MOSAICVIEW_H
