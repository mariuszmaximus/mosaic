#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include <QImage>

QImage createImage(int width, int height);
QImage createImageRandomSize();

// L2 difference between images
float distanceBetweenImages(const QImage& image1, const QImage& image2);
float distanceBetweenImages(const QString& masterFileName,
                            const QImage& image1);

/**
 * @brief Checks images for equality.
 *
 * If images are different the actual image is dumped to a file.
 *
 * @param masterFileName Image to compare against.
 * @param image          The image to check.
 * @param tolerance      Tolerance for comparison.  If distanceBetweenImages
 *                       is less than tolerance the images are considered equal.
 * @param fileName       The file to which to dump image if the images are
 *                       not equal.
 * @return               True if the images are equal to within tolerance,
 *                       Otherwise returns false.
 */
bool imagesEqual(const QString& masterFileName,
                 const QImage& image,
                 float tolerance,
                 const QString& fileName);

bool imagesEqual(const QImage& masterImage,
                 const QImage& image,
                 float tolerance,
                 const QString& fileName);

#endif // TEST_UTILITIES_H
