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
