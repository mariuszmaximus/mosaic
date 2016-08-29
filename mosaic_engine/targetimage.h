#ifndef MOTARGETIMAGE_H
#define MOTARGETIMAGE_H

#include <QImage>


class MoTargetImage {
public:
    MoTargetImage(QImage image, QSize targetSize);
    QSize getSize() const;
    QImage getImage() const;
    float getWorldSize() const;

private:
    QImage image_;
    QSize size_;
};

MoTargetImage moCreateTestImage();

#endif // MOTARGETIMAGE_H
