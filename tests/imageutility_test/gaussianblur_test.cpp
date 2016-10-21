#include <gtest/gtest.h>
#include <imageutilities.h>
#include <test_utilities.h>


TEST(GaussianBlur, IsIdentityOnConstantImage) {
    QImage img{createImage(70, 80)};
    img.fill(QColor(200, 100, 100));
    QImage img2{moGaussianBlur(img, 3.5f)};
    EXPECT_TRUE(imagesEqual(img, img2, 1.0e-4,
                            "GaussianBlurIsIdentityOnConstantImage.png"));
}

TEST(GaussianBlur, OfAnImage) {
    QImage img(":/testimages/gaussianBlur0.JPG");
    ASSERT_FALSE(img.isNull());
    QImage blurredImage = moGaussianBlur(img, 20.0f);
    blurredImage.save("blurredImage.png");
}
