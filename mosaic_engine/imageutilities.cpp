#include <imageutilities.h>
#include <iostream>


QImage moGaussianBlur(const QImage &input, float sigma) {
    Q_ASSERT(input.format() == QImage::Format_ARGB32);
    Q_UNUSED(sigma);

    int w = input.width();
    int h = input.height();

    std::vector<unsigned char> transposedImage(w * h * 3);

    // First pass
    Q_ASSERT(input.byteCount() > w * 4);
    for (int i = 0; i < h; ++i) {
        const QRgb* line =
                reinterpret_cast<const QRgb*>(input.constScanLine(i));
        for (int j = 0; j < w; ++j) {
            transposedImage[3 * (j * h + i) + 0] = qRed(line[j]);
            transposedImage[3 * (j * h + i) + 1] = qGreen(line[j]);
            transposedImage[3 * (j * h + i) + 2] = qBlue(line[j]);
        }
    }

    // Second pass
    QImage blurredImage(w, h, input.format());
    for (int i = 0; i < h; ++i) {
            QRgb* line =
                    reinterpret_cast<QRgb*>(blurredImage.scanLine(i));
        for (int j = 0; j < w; ++j) {
            line[j] = QColor(
                        transposedImage[3 * (j * h + i) + 0],
                        transposedImage[3 * (j * h + i) + 1],
                        transposedImage[3 * (j * h + i) + 2]).rgba();
        }
    }

    return blurredImage;
}
