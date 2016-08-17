#include <gtest/gtest.h>
#include <targetimage.h>

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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
