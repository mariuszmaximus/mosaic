#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include <QImage>

QImage createImage(int width, int height);
QImage createImageRandomSize();

// L2 difference between images
float distanceBetweenImages(const QImage& image1, const QImage& image2);
float distanceBetweenImages(const QImage &image1, const QString& fileName);

#endif // TEST_UTILITIES_H
