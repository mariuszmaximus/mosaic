#include <gtest/gtest.h>
#include <badnesscomposite.h>

#include <memory>


TEST(MoBadnessComposite, Constructor) {
    std::unique_ptr<MoBadnessComposite> badness;
    EXPECT_NO_THROW(badness.reset(new MoBadnessComposite));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
