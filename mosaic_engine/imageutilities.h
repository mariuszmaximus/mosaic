#ifndef IMAGEUTILITIES_H
#define IMAGEUTILITIES_H

#include <QImage>


QImage moGaussianBlur(const QImage& input, float sigma);
float moDistanceBetweenImages(const QImage &image1, const QImage &image2);

#endif // IMAGEUTILITIES_H
