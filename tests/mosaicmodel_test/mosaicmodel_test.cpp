#include <gtest/gtest.h>
#include <mosaicmodel.h>
#include <test_utilities.h>
#include <memory>
#include <cmath>


TEST(MoMosaicModel, CanBeConstructed) {
    std::unique_ptr<MoMosaicModel> model(new MoMosaicModel);
    ASSERT_NE(model, nullptr);
}

class MosaicModel : public ::testing::Test {
public:
    void SetUp() {
        numTiles = 10;
        model.resize(numTiles);
    }
    MoMosaicModel model;
    int numTiles;
};

TEST_F(MosaicModel, Resizing) {
    model.resize(14);
    ASSERT_EQ(14, model.size());
}

TEST_F(MosaicModel, CanSetXCoords) {
    float xVal = 2.0f;
    std::vector<float> xCoords(numTiles, xVal);
    model.setXCoords(&xCoords[0], &xCoords[0] + numTiles);
    std::vector<float> out(numTiles);
    model.getXCoords(&out[0]);
    ASSERT_FLOAT_EQ(out[2], xVal);
}

TEST_F(MosaicModel, CanSetYCoords) {
    float yVal = 2.0f;
    std::vector<float> yCoords(numTiles, yVal);
    model.setYCoords(&yCoords[0], &yCoords[0] + numTiles);
    std::vector<float> out(numTiles);
    model.getYCoords(&out[0]);
    ASSERT_FLOAT_EQ(out[2], yVal);
}

TEST_F(MosaicModel, CanSetRotations) {
    float rotVal = 2.0f;
    std::vector<float> rotations(numTiles, rotVal);
    model.setRotations(&rotations[0], &rotations[0] + numTiles);
    std::vector<float> out(numTiles);
    model.getRotations(&out[0]);
    ASSERT_FLOAT_EQ(out[2], rotVal);
}

TEST_F(MosaicModel, CanSetScales) {
    float scaleVal = 2.0f;
    std::vector<float> scales(numTiles, scaleVal);
    model.setScales(&scales[0], &scales[0] + numTiles);
    std::vector<float> out(numTiles);
    model.getScales(&out[0]);
    ASSERT_FLOAT_EQ(out[2], scaleVal);
}

TEST_F(MosaicModel, CannotSetTooManyValues) {
    int numTilesBeingSet = numTiles + 1;
    std::vector<float> x(numTilesBeingSet);
    ASSERT_THROW(model.setXCoords(&x[0], &x[0] + numTilesBeingSet),
            std::runtime_error);
}

TEST_F(MosaicModel, CannotSetTooFewValues) {
    int numTilesBeingSet = numTiles - 1;
    std::vector<float> x(numTilesBeingSet);
    ASSERT_THROW(model.setXCoords(&x[0], &x[0] + numTilesBeingSet),
            std::runtime_error);
}

TEST_F(MosaicModel, InitialPositionsAreInsideTarget) {
    int targetWidth = 50;
    int targetHeight = 30;
    MoTargetImage targetImage(createImageRandomSize(),
                              QSize(targetWidth, targetHeight));
    std::vector<MoTile> tiles;
    tiles.push_back(MoTile());
    tiles.push_back(MoTile());
    model.constructInitialState(targetImage, tiles);
    std::vector<float> x(model.size());
    std::vector<float> y(model.size());
    model.getXCoords(&x[0]);
    model.getYCoords(&y[0]);
    float S = std::sqrt(targetWidth * targetHeight);
    float minX = -targetWidth / (2.0 * S);
    float maxX = -minX;
    float minY = -targetHeight / (2.0 * S);
    float maxY = -minY;
    for (int i = 0; i < model.size(); ++i) {
        EXPECT_LE(minX, x[i]);
        EXPECT_GE(maxX, x[i]);
        EXPECT_LE(minY, y[i]);
        EXPECT_GE(maxY, y[i]);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
