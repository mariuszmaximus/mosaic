#include <gtest/gtest.h>
#include <quadraturerule.h>

#include <cmath>


TEST(Quadrature0, Nodes) {
    ASSERT_FLOAT_EQ(MoQuadratureRule[0][MO_QUADRATURE_NODES][0],
            std::cos((2 * (1 + 0) - 1 / 2.0) / 1.0 * M_PI));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
