#include <gtest/gtest.h>

#include <test_utilities.h>

TEST(DistanceBetweenImages, IsZeroForIdenticalImages) {
    QImage img = createImage(40, 50);
    EXPECT_NEAR(0.0f, distanceBetweenImages(img, img), 1.0e-4f);
}

TEST(DistanceBetweenImages, IsLessThanOne) {
    QImage img1 = createImage(40, 50);
    QImage img2{img1.copy()};
    img2.fill(0);
    EXPECT_LE(distanceBetweenImages(img1, img2), 1.0f);
}

TEST(DistanceBetweenImages, IsNonZeroForDifferentImages) {
    QImage img1 = createImage(40, 50);
    QImage img2{img1.copy()};
    img2.fill(0);
    EXPECT_GT(distanceBetweenImages(img1, img2), 0.0f);
}

TEST(DistanceBetweenImages, IsZeroIfImageComesFromFile) {
    QImage img1 = createImage(70, 80);
    img1.fill(QColor(200, 100, 150));
    QImage img2{img1.copy()};
    EXPECT_NEAR(0.0f,
                distanceBetweenImages(img1,
                                      "IsZeroIfImageComesFromFile_master.png"),
                1.0e-4);
}

TEST(DistanceBetweenImages, IsNonZeroIfImageDiffersFromMaster) {
    QImage img1 = createImage(70, 80);
    img1.fill(QColor(100, 100, 150));
    QImage img2{img1.copy()};
    EXPECT_LT(2.0e-2f,
                distanceBetweenImages(img1,
                                      "IsZeroIfImageComesFromFile_master.png"));
}
