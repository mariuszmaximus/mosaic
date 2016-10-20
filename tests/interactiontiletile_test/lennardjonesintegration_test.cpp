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
    std::vector<float> scales(numTiles, 1.0f);
    model.setScales(&scales[0], &scales[0] + numTiles);
    return model;
}

struct TileTileLennardJones : public ::testing::Test {
    TileTileLennardJones() :
        model(createSomeModel(2)),
        interaction(new MoInteractionTileTile(
                        std::unique_ptr<MoPotential>(
                        new MoPotentialLennardJones(
                            MoLennardJones(3.4f, 2.3f)))))
    {}
    virtual ~TileTileLennardJones() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
    void setLennardJones(const MoLennardJones& lj) {
        interaction.reset(new MoInteractionTileTile(
                        std::unique_ptr<MoPotential>(
                        new MoPotentialLennardJones(lj))));
    }
    MoMosaicModel model;
    std::unique_ptr<MoInteractionTileTile> interaction;
};


TEST_F(TileTileLennardJones, IsNonZero) {
    EXPECT_NE(0, interaction->computeBadness(model, model.getTargetImage()));
}

TEST_F(TileTileLennardJones, IsFinite) {
    float badness = interaction->computeBadness(model, model.getTargetImage());
    EXPECT_TRUE(std::isfinite(badness));
}

TEST_F(TileTileLennardJones, IsPositiveWhenTilesClose) {
    std::vector<float> widths(model.size());
    float* x = model.getXCoords();
    x[0] = 0.0f;
    x[1] = 0.5f * widths[1];
    float* y = model.getXCoords();
    y[0] = 0.0f;
    y[1] = 0.0f;

    setLennardJones(MoLennardJones(1.0f, 1.0f));
    float badness = interaction->computeBadness(model, model.getTargetImage());
    EXPECT_GT(badness, 0.0f);
}

TEST_F(TileTileLennardJones, IsNegativeWhenTilesSeparated) {
    const float sigma = 10.0f;
    std::vector<float> widths(model.size());
    model.getWidths(&widths[0]);
    float* x = model.getXCoords();
    x[0] = 0.0f;
    // Make tiles non-overlapping
    x[1] = 0.5f * (widths[0] + widths[1]) + sigma;
    float* y = model.getYCoords();
    y[0] = 0.0f;
    y[1] = 0.0f;

    setLennardJones(MoLennardJones(1.0f, sigma));
    float badness = interaction->computeBadness(model, model.getTargetImage());
    EXPECT_LT(badness, 0.0f);
}
