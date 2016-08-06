#include <gtest/gtest.h>
#include <mosaicmodel.h>

TEST(MoMosaicView, CanBeConstructed) {
    MoMosaicModel* model = new MoMosaicModel;
    ASSERT_NE(model, nullptr);
    delete model;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
