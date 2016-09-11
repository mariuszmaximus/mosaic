#include <gtest/gtest.h>
#include <quadraturerule.h>

#include <cmath>


TEST(QuadratureRuleSpotTests, Order0) {
    EXPECT_NEAR(0.0f, MoQuadratureRule[0][MO_QUADRATURE_NODES][0], 1.0e-6f);
    EXPECT_NEAR(2.0f, MoQuadratureRule[0][MO_QUADRATURE_WEIGHTS][0], 1.0e-6f);
}

TEST(QuadratureRuleSpotTests, Order1) {
    EXPECT_NEAR(MoQuadratureRule[1][MO_QUADRATURE_NODES][0],
            -MoQuadratureRule[1][MO_QUADRATURE_NODES][1],
            1.0e-6f);
    EXPECT_NEAR(1.0f, MoQuadratureRule[1][MO_QUADRATURE_WEIGHTS][0], 1.0e-6f);
    EXPECT_NEAR(1.0f, MoQuadratureRule[1][MO_QUADRATURE_WEIGHTS][1], 1.0e-6f);
    float totalWeight = 0;
    for (int i = 0; i < 2; ++i) {
        totalWeight += MoQuadratureRule[1][MO_QUADRATURE_WEIGHTS][i];
    }
    EXPECT_NEAR(2.0f, totalWeight, 1.0e-6f);
}

TEST(QuadratureRuleSpotTests, Order2) {
    EXPECT_NEAR(0.0f, MoQuadratureRule[2][MO_QUADRATURE_NODES][1], 1.0e-7);
    EXPECT_NEAR(MoQuadratureRule[2][MO_QUADRATURE_NODES][0],
            -MoQuadratureRule[2][MO_QUADRATURE_NODES][2],
            1.0e-6f);
    EXPECT_NEAR(MoQuadratureRule[2][MO_QUADRATURE_WEIGHTS][0],
            MoQuadratureRule[2][MO_QUADRATURE_WEIGHTS][2],
            1.0e-6f);
    EXPECT_NEAR(8.0f / 9.0f, MoQuadratureRule[2][MO_QUADRATURE_WEIGHTS][1], 1.0e-6f);
    float totalWeight = 0;
    for (int i = 0; i < 3; ++i) {
        totalWeight += MoQuadratureRule[2][MO_QUADRATURE_WEIGHTS][i];
    }
    EXPECT_NEAR(2.0f, totalWeight, 1.0e-6f);
}

TEST(QuadratureRuleSpotTests, Order3) {
    EXPECT_NEAR(MoQuadratureRule[3][MO_QUADRATURE_NODES][0],
            -MoQuadratureRule[3][MO_QUADRATURE_NODES][3],
            1.0e-6f);
    EXPECT_NEAR(MoQuadratureRule[3][MO_QUADRATURE_NODES][1],
            -MoQuadratureRule[3][MO_QUADRATURE_NODES][2],
            1.0e-6f);
    EXPECT_NEAR(-std::sqrt(3.0 / 7.0 + 2.0/ 7.0 * sqrt(6.0 / 5.0)),
                MoQuadratureRule[3][MO_QUADRATURE_NODES][0],
            1.0e-6f);
    EXPECT_NEAR(-std::sqrt(3.0 / 7.0 - 2.0/ 7.0 * sqrt(6.0 / 5.0)),
                MoQuadratureRule[3][MO_QUADRATURE_NODES][1],
            1.0e-6f);
    float totalWeight = 0;
    for (int i = 0; i < 4; ++i) {
        totalWeight += MoQuadratureRule[3][MO_QUADRATURE_WEIGHTS][i];
    }
    EXPECT_NEAR(2.0f, totalWeight, 1.0e-6f);
}

static float f(float x) {
    return 7.0f * x * x * x -8.0f * x * x - 3.0f * x + 3.0f;
}

TEST(ExampleQuadrature, Order1) {
    float integral = 0.0f;
    for (int i = 0; i < 2; ++i) {
        integral += MoQuadratureRule[1][MO_QUADRATURE_WEIGHTS][i] *
                f(MoQuadratureRule[1][MO_QUADRATURE_NODES][i]);
    }
    EXPECT_NEAR(2.0f / 3.0f, integral, 1.0e-6);
}

TEST(ExampleQuadrature, Order2) {
    float integral = 0.0f;
    for (int i = 0; i < 3; ++i) {
        integral += MoQuadratureRule[2][MO_QUADRATURE_WEIGHTS][i] *
                f(MoQuadratureRule[2][MO_QUADRATURE_NODES][i]);
    }
    EXPECT_NEAR(2.0f / 3.0f, integral, 1.0e-6);
}

TEST(ExampleQuadrature, Order3) {
    float integral = 0.0f;
    for (int i = 0; i < 4; ++i) {
        integral += MoQuadratureRule[3][MO_QUADRATURE_WEIGHTS][i] *
                f(MoQuadratureRule[3][MO_QUADRATURE_NODES][i]);
    }
    EXPECT_NEAR(2.0f / 3.0f, integral, 1.0e-6);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
