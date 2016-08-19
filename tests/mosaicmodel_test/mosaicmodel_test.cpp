#include <gtest/gtest.h>
#include <mosaicmodel.h>
#include <memory>

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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
