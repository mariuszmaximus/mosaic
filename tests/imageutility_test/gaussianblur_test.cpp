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

static void makeRightHalfOfImageBlack(QImage* image) {
    for (int i = 0; i < image->height(); ++i) {
        for (int j = image->width() / 2; j < image->width(); ++j) {
            image->setPixel(j, i, QColor(0, 0, 0).rgba());
        }
    }
}

TEST(GaussianBlur, SoftensAHardEdge) {
    QImage img(30, 20, QImage::Format_ARGB32);
    QColor color(150, 100, 200);
    img.fill(color);
    makeRightHalfOfImageBlack(&img);
    QImage blurredImage{moGaussianBlur(img, 3.0f)};

    QColor pixel;

    // pixels more than a few sigma away from the hard edge are unchanged.
    pixel = blurredImage.pixel(2, 4);
    EXPECT_NEAR(color.redF(), pixel.redF(), 1.0e-2);
    EXPECT_NEAR(color.greenF(), pixel.greenF(), 1.0e-2);
    EXPECT_NEAR(color.blueF(), pixel.blueF(), 1.0e-2);

    pixel = blurredImage.pixel(img.width() - 2, 4);
    EXPECT_NEAR(0.0f, pixel.redF(), 1.0e-2);
    EXPECT_NEAR(0.0f, pixel.greenF(), 1.0e-2);
    EXPECT_NEAR(0.0f, pixel.blueF(), 1.0e-2);

    // A pixel near the hard edge has intermediate color
    pixel = blurredImage.pixel(img.width() / 2, 4);
    EXPECT_LT(0.0f, pixel.redF());
    EXPECT_LT(0.0f, pixel.greenF());
    EXPECT_LT(0.0f, pixel.blueF());
    EXPECT_LT(pixel.redF(), color.redF());
    EXPECT_LT(pixel.greenF(), color.greenF());
    EXPECT_LT(pixel.blueF(), color.blueF());
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
