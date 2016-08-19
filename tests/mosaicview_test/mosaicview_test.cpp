#include <gtest/gtest.h>
#include <mosaicview.h>

TEST(MoMosaicView, CanBeConstructed) {
    std::unique_ptr<MoMosaicView> view(new MoMosaicView);
    ASSERT_NE(view, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
