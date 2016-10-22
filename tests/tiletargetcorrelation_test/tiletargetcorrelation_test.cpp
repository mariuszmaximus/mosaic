#include <gtest/gtest.h>
#include <tiletargetcorrelation.h>
#include <targetimage.h>
#include <mosaicmodel.h>

#include <memory>


TEST(MoTileTargetCorrelation, IncludeTest) {
  EXPECT_TRUE(true);
}

TEST(MoTileTargetCorrelation, Constructor) {
    std::unique_ptr<MoTileTargetCorrelation> ptr;
    EXPECT_NO_THROW(ptr.reset(new MoTileTargetCorrelation(10)));
}

TEST(MoTileTargetCorrelation, OfEmptyModelIsZero) {
    MoTileTargetCorrelation tileTargetCorrelation(10);
    MoMosaicModel model;
    MoTargetImage targetImage(QImage(), QSize(40, 30));
    EXPECT_FLOAT_EQ(0.0f,
                    tileTargetCorrelation.computeBadness(model, targetImage));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
