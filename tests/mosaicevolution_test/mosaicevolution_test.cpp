#include <gtest/gtest.h>
#include <mosaicevolution.h>

TEST(MoMosaicEvolution, CanBeConstructed) {
    MoMosaicEvolution* view = new MoMosaicEvolution;
    ASSERT_NE(view, nullptr);
    delete view;
}

TEST(MoMosaicEvolution, CurrentModelIsNullBeforeInitialStateIsSet) {
    MoMosaicEvolution view;
    MoMosaicModel* model = view.getCurrentModel();
    ASSERT_NE(model, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
