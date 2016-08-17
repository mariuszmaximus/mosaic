#include <gtest/gtest.h>
#include <mosaicevolution.h>
#include <mosaicmodel.h>

TEST(MoMosaicEvolution, CanBeConstructed) {
    MoMosaicEvolution* view = new MoMosaicEvolution;
    ASSERT_NE(view, nullptr);
    delete view;
}

TEST(MoMosaicEvolution, ModelIsEmptyBeforeSettingInitialState) {
    MoMosaicEvolution view;
    MoMosaicModel* model = view.getCurrentModel();
    ASSERT_EQ(0, model->size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
