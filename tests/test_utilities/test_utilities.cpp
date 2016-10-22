#include <test_utilities.h>

#include <random>
#include <QFileInfo>
#include <imageutilities.h>


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

float distanceBetweenImages(const QString& fileName, const QImage &image1) {
    QImage image2(fileName);
    if (image2.format() != QImage::Format_ARGB32) {
        image2 = image2.convertToFormat(QImage::Format_ARGB32);
    }
    return moDistanceBetweenImages(image1, image2);
}

static bool closeEnough(float distance, float tolerance,
                        const QImage& masterImage,
                        const QImage& image,
                        const QString& fileName) {
    if (distance < tolerance) {
        return true;
    } else {
        image.save(fileName);
        QFileInfo info(fileName);
        QString masterFileName =
                info.path() +
                "/" +
                info.completeBaseName() +
                "_master.png";
        masterImage.save(masterFileName);
        return false;
    }
}

bool imagesEqual(const QString &masterFileName,
                 const QImage &image,
                 float tolerance,
                 const QString &fileName) {
    QImage masterImage(masterFileName);
    float distance = moDistanceBetweenImages(masterImage, image);
    return closeEnough(distance, tolerance, masterImage, image, fileName);
}

bool imagesEqual(const QImage &masterImage,
                 const QImage &image,
                 float tolerance,
                 const QString &fileName) {
    float distance = moDistanceBetweenImages(masterImage, image);
    return closeEnough(distance, tolerance, masterImage, image, fileName);
}
