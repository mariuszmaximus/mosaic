#ifndef QUADRATURE_RULE_H
#define QUADRATURE_RULE_H

#include <cmath>

#define MO_QUADRATURE_NODES 0
#define MO_QUADRATURE_WEIGHTS 1


float MoQuadratureRule[4][2][4] = {
    {{std::cos((2.0f * (1 + 0) - 1) * M_PI / (2.0f * 1.0f)), 0, 0, 0},
     {0, 0, 0, 0}},
    {{0, 0, 0, 0},
     {0, 0, 0, 0}},
    {{0, 0, 0, 0},
     {0, 0, 0, 0}},
    {{0, 0, 0, 0},
     {0, 0, 0, 0}}
};
#endif // QUADRATURE_H
