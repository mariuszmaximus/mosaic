#include <gtest/gtest.h>
#include <potentiallennardjones.h>
#include <interactiontiletile.h>
#include <mosaicmodel.h>
#include <targetimage.h>
#include <cmath>


static MoMosaicModel createSomeModel(int numTiles) {
    MoMosaicModel model;
    std::vector<MoTile> tiles(numTiles,
                              MoTile(QImage(20, 30, QImage::Format_RGBA8888)));
    MoTargetImage targetImage(QImage(300, 200, QImage::Format_RGBA8888),
                              QSize(3000, 2000));
    model.constructInitialState(targetImage, tiles);
    std::vector<float> x(numTiles);
    model.setXCoords(&x[0], &x[0] + numTiles);
    std::vector<float> y(numTiles);
    model.setXCoords(&y[0], &y[0] + numTiles);
    std::vector<float> rotations(numTiles, 0.0f);
    model.setRotations(&rotations[0], &rotations[0] + numTiles);
    std::vector<float> scales(numTiles, 0.0f);
    model.setRotations(&scales[0], &scales[0] + numTiles);
    return model;
}

struct TileTileLennardJones : public ::testing::Test {
    TileTileLennardJones() :
        epsilon{3.4f},
        sigma{2.3f},
        model(createSomeModel(2)),
        interaction(std::unique_ptr<MoPotential>(
                        new MoPotentialLennardJones(
                            MoLennardJones(epsilon, sigma))))
    {}
    virtual ~TileTileLennardJones() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
    const float epsilon;
    const float sigma;
    MoMosaicModel model;
    MoInteractionTileTile interaction;
};


TEST_F(TileTileLennardJones, IsNonZero) {
    EXPECT_NE(0, interaction.computeBadness(model, model.getTargetImage()));
}

TEST_F(TileTileLennardJones, IsFinite) {
    float badness = interaction.computeBadness(model, model.getTargetImage());
    EXPECT_TRUE(std::isfinite(badness));
}
