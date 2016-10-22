#include <gtest/gtest.h>
#include <tiletargetcorrelation.h>

#include <memory>


TEST(MoTileTargetCorrelation, IncludeTest) {
  EXPECT_TRUE(true);
}

TEST(MoTileTargetCorrelation, Constructor) {
    std::unique_ptr<MoTileTargetCorrelation> ptr;
    EXPECT_NO_THROW(ptr.reset(new MoTileTargetCorrelation(10)));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
