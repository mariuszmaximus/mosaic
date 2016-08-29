#include "targetimage.h"
#include <cmath>


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

float MoTargetImage::getWorldSize() const {
    return std::sqrt(size_.width() * size_.height());
}

MoTargetImage moCreateTestImage() {
    QSize size(22, 33);
    QImage image(size, QImage::Format_ARGB32);
    image.fill(QColor(200, 100, 10));
    return MoTargetImage(image, size);
}
