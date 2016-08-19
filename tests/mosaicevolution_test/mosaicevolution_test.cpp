#include <gtest/gtest.h>
#include <mosaicevolution.h>
#include <mosaicmodel.h>
#include <mosaicupdate.h>
#include <tile.h>
#include <targetimage.h>
#include <memory>


TEST(MoMosaicEvolution, CanBeConstructed) {
    std::unique_ptr<MoMosaicEvolution> evolution(new MoMosaicEvolution);
    ASSERT_NE(evolution, nullptr);
}

struct MosaicEvolution : public ::testing::Test {
    MoMosaicEvolution evolution;
};

TEST_F(MosaicEvolution, ModelIsEmptyBeforeSettingInitialState) {
    MoMosaicModel* model = evolution.getCurrentModel();
    ASSERT_EQ(0, model->size());
}

TEST_F(MosaicEvolution, CanTakeStepWithoutUpdaters) {
    ASSERT_NO_THROW(evolution.takeStep());
}

struct IdentityUpdate : public MoMosaicUpdate {
    void update(MoMosaicModel *model) {
        Q_UNUSED(model);
    }
};

TEST_F(MosaicEvolution, CanAddUpdate) {
    std::unique_ptr<MoMosaicUpdate> update(new IdentityUpdate);
    ASSERT_NO_THROW(evolution.addUpdate(std::move(update)));
}

TEST_F(MosaicEvolution, IdentityUpdateDoesNotChangeModel) {
    std::unique_ptr<MoMosaicUpdate> update(new IdentityUpdate);
    evolution.addUpdate(std::move(update));
    std::vector<MoTile> tiles;
    evolution.constructInitialState(moCreateTestImage(),
                                    tiles);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
