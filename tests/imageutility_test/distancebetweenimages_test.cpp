#include <gtest/gtest.h>
#include <QFileInfo>

#include <test_utilities.h>
#include <imageutilities.h>


TEST(DistanceBetweenImages, IsZeroForIdenticalImages) {
    QImage img = createImage(40, 50);
    EXPECT_NEAR(0.0f, moDistanceBetweenImages(img, img), 1.0e-4f);
}

TEST(DistanceBetweenImages, IsLessThanOne) {
    QImage img1 = createImage(40, 50);
    QImage img2{img1.copy()};
    img2.fill(0);
    EXPECT_LE(moDistanceBetweenImages(img1, img2), 1.0f);
}

TEST(DistanceBetweenImages, IsNonZeroForDifferentImages) {
    QImage img1 = createImage(40, 50);
    QImage img2{img1.copy()};
    img2.fill(0);
    EXPECT_GT(moDistanceBetweenImages(img1, img2), 0.0f);
}

TEST(DistanceBetweenImages, IsZeroIfImageComesFromFile) {
    QImage img1 = createImage(70, 80);
    img1.fill(QColor(200, 100, 150));
    EXPECT_NEAR(0.0f,
                distanceBetweenImages("IsZeroIfImageComesFromFile_master.png",
                                      img1),
                1.0e-4);
}

TEST(DistanceBetweenImages, IsNonZeroIfImageDiffersFromMaster) {
    QImage img1 = createImage(70, 80);
    img1.fill(QColor(100, 100, 150));
    QImage img2{img1.copy()};
    EXPECT_LT(2.0e-2f,
                distanceBetweenImages("IsZeroIfImageComesFromFile_master.png",
                                      img1));
}

TEST(ImagesEqual, DoesNotDumpIfImagesAreEqual) {
    QImage img = createImage(70, 80);
    img.fill(QColor(200, 100, 150));
    QString fileName{"ThisFileIsNotWritten.png"};
    ASSERT_TRUE(imagesEqual("IsZeroIfImageComesFromFile_master.png",
                          img,
                          1.0e-4f,
                          fileName));
    QFileInfo fileInfo(fileName);
    EXPECT_FALSE(fileInfo.exists());
}


TEST(ImagesEqual, DumpsFileIfImagesAreNotEqual) {
    QImage img = createImage(70, 80);
    img.fill(QColor(100, 100, 150));
    QString fileName{"ThisFileIsWritten.png"};
    ASSERT_FALSE(imagesEqual("IsZeroIfImageComesFromFile_master.png",
                          img,
                          1.0e-4f,
                          fileName));
    QFileInfo fileInfo(fileName);
    EXPECT_TRUE(fileInfo.exists());
}
