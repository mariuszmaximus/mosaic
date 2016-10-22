#include <gtest/gtest.h>
#include <imageutilities.h>
#include <test_utilities.h>


TEST(GaussianBlur, IsIdentityOnConstantImage) {
    QImage img{createImage(70, 80)};
    QColor color(200, 0, 0);
    img.fill(color);
    QImage img2{moGaussianBlur(img, 3.5f)};
    EXPECT_TRUE(imagesEqual(img, img2, 1.0e-2,
                            "GaussianBlurIsIdentityOnConstantImage.png"));
    // Some more spot tests:
    QColor pixel1(img2.pixel(10, 10));
    EXPECT_NEAR(color.redF(), pixel1.redF(), 1.0e-2);
    EXPECT_NEAR(color.greenF(), pixel1.greenF(), 1.0e-2);
    EXPECT_NEAR(color.blueF(), pixel1.blueF(), 1.0e-2);
}

TEST(GaussianBlur, OfAnImage) {
    QImage img(":/testimages/GaussianBlurOfAnImage_input.png");
    ASSERT_FALSE(img.isNull());
    img = img.convertToFormat(QImage::Format_ARGB32);
    ASSERT_EQ(QImage::Format_ARGB32, img.format());
    QImage blurredImage = moGaussianBlur(img, 5.0f);
    EXPECT_TRUE(imagesEqual("GaussianBlurOfAnImage_master.png",
                            blurredImage, 1.0e-3f,
                            "GaussianBlurOfAnImage.png"));
}
