#include <gtest/gtest.h>
#include <targetimage.h>
#include <cmath>


TEST(MoTargetImage, CanBeConstructed) {
    moCreateTestImage();
}

TEST(MoTargetImage, GetSize) {
    MoTargetImage targetImage(QImage(), QSize(100, 200));
    QSize size = targetImage.getSize();
    ASSERT_EQ(QSize(100, 200), size);
}

TEST(MoTargetImage, GetImage) {
    MoTargetImage targetImage(QImage(), QSize(100, 200));
    QImage image(targetImage.getImage());
    ASSERT_TRUE(image.isNull());
}

TEST(MoTargetImage, GetWorldSize) {
    int width = 200;
    int height = 100;
    MoTargetImage targetImage(QImage(), QSize(width, height));
    float worldSize = targetImage.getWorldSize();
    ASSERT_FLOAT_EQ(std::sqrt(width * height), worldSize);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
