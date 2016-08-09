#include <mosaicimageprovider.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicImageProvider::MoMosaicImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image),
    renderer_(new MoMosaicViewRenderer) {
}

MoMosaicImageProvider::~MoMosaicImageProvider() {
    delete renderer_;
}


void MoMosaicImageProvider::setModel(std::shared_ptr<MoMosaicModel> model) {
    renderer_->setModel(model);
}

std::shared_ptr<MoMosaicModel> MoMosaicImageProvider::getModel() const {
    return renderer_->getModel();
}

QImage MoMosaicImageProvider::requestImage(const QString &id, QSize *size,
                                           const QSize &requestedSize) {
    Q_UNUSED(id);
    QImage image = emptyImage(requestedSize);
    image = image.scaled(requestedSize, Qt::KeepAspectRatio);
    *size = image.size();
    return image;
}

QImage MoMosaicImageProvider::emptyImage(const QSize& size) const {
    QImage result(size, QImage::Format_RGB888);
    result.fill(Qt::green);
    return result;
}
