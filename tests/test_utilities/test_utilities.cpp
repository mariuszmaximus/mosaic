#include <test_utilities.h>

#include <random>


static std::random_device rd;
static std::mt19937 gen(rd());

QImage createImage(int width, int height) {
    QImage image(width, height, QImage::Format_ARGB32);
    static std::uniform_int_distribution<> dis(0, 255);
    int r = dis(gen);
    int g = dis(gen);
    int b = dis(gen);
    image.fill(QColor(r, g, b));
    return image;
}

QImage createImageRandomSize() {
    static const int min = 20;
    static const int max = 100;
    static std::uniform_int_distribution<> dis(min, max);
    int width = dis(gen);
    int height = dis(gen);
    return createImage(width, height);
}

float distanceBetweenImages(const QImage &image1, const QImage &image2) {
    Q_ASSERT(image1.format() == QImage::Format_ARGB32);
    Q_ASSERT(image2.format() == QImage::Format_ARGB32);

    // Rescale image2 to the same size as image1 if needed
    QImage image2Resized;
    QSize size = image1.size();
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
                reinterpret_cast<const QRgb*>(image1.constScanLine(i));
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
