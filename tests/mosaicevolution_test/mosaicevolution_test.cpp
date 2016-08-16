#include <gtest/gtest.h>
#include <mosaicevolution.h>

TEST(MoMosaicEvolution, CanBeConstructed) {
    MoMosaicEvolution* view = new MoMosaicEvolution;
    ASSERT_NE(view, nullptr);
    delete view;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
