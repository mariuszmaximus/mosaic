#include <imageutilities.h>


QImage moGaussianBlur(const QImage &input, float sigma) {
    Q_UNUSED(sigma);

    int w = input.width();
    int h = input.height();

    int pitch = w;
    std::vector<unsigned char> transposedImage(pitch * h * 3);

    // First pass
    for (int i = 0; i < h; ++i) {
        const QRgb* line =
                reinterpret_cast<const QRgb*>(input.constScanLine(i));
        for (int j = 0; j < w; ++j) {
            QColor color{line[j]};
            transposedImage[3 * (i * pitch + j) + 0] = color.red();
            transposedImage[3 * (i * pitch + j) + 1] = color.green();
            transposedImage[3 * (i * pitch + j) + 2] = color.blue();
        }
    }

    // Second pass
    QImage blurredImage(w, h, input.format());
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            QRgb* line =
                    reinterpret_cast<QRgb*>(blurredImage.scanLine(j));
            line[i] = QColor(
                        transposedImage[3 * (i * pitch + j) + 0],
                        transposedImage[3 * (i * pitch + j) + 1],
                        transposedImage[3 * (i * pitch + j) + 2]).rgb();
        }
    }

    return blurredImage;
}
