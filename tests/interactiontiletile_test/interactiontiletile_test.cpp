#include <gtest/gtest.h>
#include <interactiontiletile.h>


TEST(MoInteractionTileTile, Constructor) {
    std::unique_ptr<MoInteractionTileTile> interaction;
    EXPECT_NO_THROW(interaction.reset(new MoInteractionTileTile(nullptr)));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
