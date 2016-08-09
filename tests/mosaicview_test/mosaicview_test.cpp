#include <gtest/gtest.h>
#include <mosaicimageprovider.h>

TEST(MoMosaicImageProvider, CanBeConstructed) {
    MoMosaicImageProvider* view = new MoMosaicImageProvider;
    ASSERT_NE(view, nullptr);
    delete view;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
