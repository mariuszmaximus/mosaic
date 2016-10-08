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
    float range() const {
        return -1.0f;
    }
};


struct MoInteractionTileTileIdentity : public ::testing::Test {
    MoInteractionTileTileIdentity() :
        interaction(std::unique_ptr<MoPotential>(new IdentityPotential())),
        model(),
        targetImage(QImage(), QSize(150, 100))
    {}
    virtual void SetUp() {
        createSomeModel(2);
    }
    virtual void TearDown() {}
    void createSomeModel(int numTiles) {
        std::vector<MoTile> tiles(numTiles,
            MoTile(QImage(20, 30, QImage::Format_RGBA8888)));
        model.constructInitialState(targetImage, tiles);
        std::vector<float> x(numTiles);
        model.setXCoords(&x[0], &x[0] + numTiles);
        std::vector<float> y(numTiles);
        model.setXCoords(&y[0], &y[0] + numTiles);
        std::vector<float> rotations(numTiles, 0.0f);
        model.setRotations(&rotations[0], &rotations[0] + numTiles);
        std::vector<float> scales(numTiles, 0.0f);
        model.setRotations(&scales[0], &scales[0] + numTiles);
    }
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

TEST_F(MoInteractionTileTileIdentity, ThreeTilesGiveThreeTimesAsMuchBadness) {
    int numTiles = 3;
    createSomeModel(numTiles);
    EXPECT_FLOAT_EQ(3.0f, interaction.computeBadness(model, targetImage));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
