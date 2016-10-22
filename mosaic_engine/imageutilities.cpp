#include <imageutilities.h>
#include <algorithm>
#include <cmath>

#ifndef MO_SQR
#define MO_SQR(a) (a) * (a)
#endif


QImage moGaussianBlur(const QImage &input, float sigma) {
    Q_ASSERT(input.format() == QImage::Format_ARGB32);
    Q_UNUSED(sigma);

    int w = input.width();
    int h = input.height();

    // This could all be much optimized by improving alignment,
    // padding, and vectorization.

    int stencilWidth = 2.0 * sigma;
    std::vector<float> stencil(2 * stencilWidth + 1);
    for (int i = 0; i < static_cast<int>(stencil.size()); ++i) {
        stencil[i] = std::exp(-MO_SQR((i - stencilWidth) / sigma));
    }
    float normalization = std::accumulate(stencil.begin(), stencil.end(), 0.0f);
    for (int i = 0; i < static_cast<int>(stencil.size()); ++i) {
        stencil[i] /= normalization;
    }


    std::vector<unsigned char> tempImage(w * h * 3);

    Q_ASSERT(input.byteCount() > w * 4);
    asm("# First pass");
    for (int i = 0; i < h; ++i) {
        const QRgb* line =
                reinterpret_cast<const QRgb*>(input.constScanLine(i));
        for (int j = 0; j < w; ++j) {
            asm("# gather data for first pass");
            unsigned char a[3][2 * stencilWidth + 1];
            for (int l = -stencilWidth; l <= stencilWidth; ++l) {
                int jPrime = std::max(0, std::min(j + l, w - 1));
                a[0][l + stencilWidth] = qRed(line[jPrime]);
                a[1][l + stencilWidth] = qGreen(line[jPrime]);
                a[2][l + stencilWidth] = qBlue(line[jPrime]);
            }

            asm("# Now compute the convolution along first dimension");
            float conv[3] = {0.0f};
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 2 * stencilWidth + 1; ++l) {
                    conv[k] += a[k][l] * stencil[l];
                }
                tempImage[3 * (i * w + j) + k] = conv[k];
            }
        }
    }

    // Second pass
    asm("# Second pass");
    QImage blurredImage(w, h, input.format());
    for (int i = 0; i < h; ++i) {
            QRgb* line =
                    reinterpret_cast<QRgb*>(blurredImage.scanLine(i));
        for (int j = 0; j < w; ++j) {
            asm("# gather data for second pass");
            unsigned char a[3][2 * stencilWidth + 1];
            for (int l = -stencilWidth; l <= stencilWidth; ++l) {
                int iPrime = std::max(0, std::min(i + l, h - 1));
                a[0][l + stencilWidth] = tempImage[3 * (iPrime * w + j) + 0];
                a[1][l + stencilWidth] = tempImage[3 * (iPrime * w + j) + 1];
                a[2][l + stencilWidth] = tempImage[3 * (iPrime * w + j) + 2];
            }

            asm("# Now compute the convolution along second dimension");
            float conv[3] = {0.0f};
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 2 * stencilWidth + 1; ++l) {
                    conv[k] += a[k][l] * stencil[l];
                }
            }
            line[j] = QColor(conv[0], conv[1], conv[2]).rgba();
        }
    }

    return blurredImage;
}

float moDistanceBetweenImages(const QImage &image1, const QImage &image2) {
    const QImage* image1Ptr = &image1;
    QImage image1WithFormatFixed;
    if (image1.format() != image2.format()) {
        image1WithFormatFixed = image1.convertToFormat(image2.format());
        image1Ptr = &image1WithFormatFixed;
    }
    Q_ASSERT(image1Ptr->format() == image2.format());

    // Rescale image2 to the same size as image1 if needed
    QImage image2Resized;
    QSize size = image1Ptr->size();
    if (image2.size() == size) {
        image2Resized = image2;
    } else {
        image2Resized = image2.scaled(size);
    }

    // now iterate over pixels and compute L2 distance
    int w = size.width();
    int h = size.height();
    float distance = 0.0f;
    for (int i = 0; i < h; ++i) {
        const QRgb* line1 =
                reinterpret_cast<const QRgb*>(image1Ptr->constScanLine(i));
        const QRgb* line2 =
                reinterpret_cast<const QRgb*>(image2Resized.constScanLine(i));
        for (int j = 0; j < w; ++j) {
            QColor color1(line1[j]);
            qreal rgb1[3];
            color1.getRgbF(&rgb1[0], &rgb1[1], &rgb1[2]);
            QColor color2(line2[j]);
            qreal rgb2[3];
            color2.getRgbF(&rgb2[0], &rgb2[1], &rgb2[2]);
            for (int k = 0; k < 3; ++k) {
                distance += (rgb1[k] - rgb2[k]) * (rgb1[k] - rgb2[k]);
            }
        }
    }
    distance /= (3.0f * w * h);
    distance = std::sqrt(distance);
    return distance;
}
