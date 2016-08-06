#include <gtest/gtest.h>
#include <mosaicmodel.h>

TEST(MoMosaicModel, CanBeConstructed) {
    MoMosaicModel* model = new MoMosaicModel;
    ASSERT_NE(model, nullptr);
    delete model;
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

TEST_F(MosaicModel, CanSetXCoords) {
    float xVal = 2.0f;
    std::vector<float> xCoords(numTiles, xVal);
    model.setXCoords(&xCoords[0], &xCoords[0] + numTiles);
    std::vector<float> out(numTiles);
    model.getXCoords(&out[0]);
    ASSERT_FLOAT_EQ(out[2], xVal);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
