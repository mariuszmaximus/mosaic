#include <lennardjones.h>

MoLennardJones::MoLennardJones(float epsilon, float sigma) :
    epsilon_(epsilon),
    sigma_(sigma)
{}

float MoLennardJones::evaluateAt(float r) const {
    float sigmaOverR = sigma_ / r;
    float xi = sigmaOverR * sigmaOverR;
    xi = xi * xi * xi;
    return 4.0 * epsilon_ * (xi * xi - xi);
}
