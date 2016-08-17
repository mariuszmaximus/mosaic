#include "targetimage.h"

MoTargetImage::MoTargetImage(QImage image,
                             QSize targetSize) :
    image_(image),
    size_(targetSize) {
}

QSize MoTargetImage::getSize() const {
    return size_;
}

QImage MoTargetImage::getImage() const {
    return image_;
}

MoTargetImage moCreateTestImage() {
    QSize size(22, 33);
    QImage image(size, QImage::Format_ARGB32);
    image.fill(QColor(200, 100, 10));
    return MoTargetImage(image, size);
}
