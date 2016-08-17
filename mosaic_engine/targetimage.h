#ifndef MOTARGETIMAGE_H
#define MOTARGETIMAGE_H

#include <QImage>


class MoTargetImage {
public:
    MoTargetImage(QImage image, QSize targetSize);

private:
    QImage image_;
    QSize targetSize_;
};

MoTargetImage createTestImage();

#endif // MOTARGETIMAGE_H
