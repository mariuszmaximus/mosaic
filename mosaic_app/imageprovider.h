#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>

class MoSourceImages;

class MoImageProvider : public QQuickImageProvider
{
public:
    MoImageProvider(MoSourceImages* sourceImages);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
private:
    MoSourceImages* sourceImages_;
};

#endif // IMAGEPROVIDER_H
