#include <gtest/gtest.h>
#include <interactiontiletile.h>
#include <mosaicmodel.h>
#include <targetimage.h>
#include <tile.h>

#include <QtGlobal>
#include <memory>


TEST(MoInteractionTileTile, Constructor) {
    std::unique_ptr<MoInteractionTileTile> interaction;
    EXPECT_NO_THROW(interaction.reset(new MoInteractionTileTile(nullptr)));
}


class IdentityPotential : public MoPotential {
    float operator()(const float* x1, const float* x2) {
        Q_UNUSED(x1);
        Q_UNUSED(x2);
        return 1.0f;
    }
};


struct MoInteractionTileTileIdentity : public ::testing::Test {
    MoInteractionTileTileIdentity() :
        interaction(std::unique_ptr<MoPotential>(new IdentityPotential())),
        model(),
        targetImage(QImage(), QSize(150, 100))
    {}
    virtual void SetUp() {
        std::vector<MoTile> tiles(2,
            MoTile(QImage(20, 30, QImage::Format_RGBA8888)));
        model.constructInitialState(targetImage, tiles);
        float x[] = {30.0f, 50.0f};
        model.setXCoords(&x[0], &x[2]);
        float y[] = {40.0f, 50.0f};
        model.setXCoords(&y[0], &y[2]);
        std::vector<float> rotations(2, 0.0f);
        model.setRotations(&rotations[0], &rotations[0] + 2);
        std::vector<float> scales(2, 0.0f);
        model.setRotations(&scales[0], &scales[0] + 2);
    }
    virtual void TearDown() {}
    MoInteractionTileTile interaction;
    MoMosaicModel model;
    MoTargetImage targetImage;
};


TEST_F(MoInteractionTileTileIdentity, CanComputeBadness) {
    EXPECT_NO_THROW(interaction.computeBadness(model, targetImage));
}

TEST_F(MoInteractionTileTileIdentity, UnitScaleTilesGiveBadnessOfOne) {
    EXPECT_FLOAT_EQ(1.0f, interaction.computeBadness(model, targetImage));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
