#include <gtest/gtest.h>
#include <interactiontileborder.h>
#include <potential.h>

#include <QtGlobal>


TEST(MoInteractionTileBorder, Constructor) {
    std::unique_ptr<MoInteractionTileBorder> interaction;
    EXPECT_NO_THROW(interaction.reset(new MoInteractionTileBorder(nullptr)));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
