#include <gtest/gtest.h>
#include <badnesscomposite.h>
#include <mosaicmodel.h>
#include <targetimage.h>

#include <memory>
#include <QtGlobal>


TEST(MoBadnessComposite, Constructor) {
    std::unique_ptr<MoBadnessComposite> badness;
    EXPECT_NO_THROW(badness.reset(new MoBadnessComposite));
}

struct MoBadnessCompositeT : public ::testing::Test {
    MoBadnessCompositeT()  :
        model(),
        targetImage(QImage(), QSize(400, 300))
    {}
    virtual ~MoBadnessCompositeT() {}
    virtual void SetUp() {
        createSomeModel(2);
    }
    virtual void TearDown() { }
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
        std::vector<float> scales(numTiles, 1.0f);
        model.setScales(&scales[0], &scales[0] + numTiles);
    }
    MoMosaicModel model;
    MoTargetImage targetImage;
};

TEST_F(MoBadnessCompositeT, EmptyCompositeHasZeroBadness) {
    MoBadnessComposite badness;
    EXPECT_EQ(0.0f, badness.computeBadness(model, targetImage));
}

class ConstantBadness : public MoBadness {
    virtual ~ConstantBadness() {}
    float computeBadness(const MoMosaicModel &model, const MoTargetImage &targetImage) {
        Q_UNUSED(model);
        Q_UNUSED(targetImage);
        return 2.3f;
    }
};

TEST_F(MoBadnessCompositeT, NonEmptyBadnessHasNonZeroBadness) {
    MoBadnessComposite badness;
    badness.addBadness(std::unique_ptr<MoBadness>(new ConstantBadness));
    EXPECT_NE(0.0f, badness.computeBadness(model, targetImage));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
