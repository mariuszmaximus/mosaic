#include "imageprovider.h"
#include "sourceimages.h"


MoImageProvider::MoImageProvider(MoSourceImages* sourceImages) :
    QQuickImageProvider(QQuickImageProvider::Image),
    sourceImages_(sourceImages)
{
}

QImage MoImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage image = sourceImages_->getImage(id);
    image = image.scaled(requestedSize, Qt::KeepAspectRatio);
    *size = image.size();
    return image;
}
