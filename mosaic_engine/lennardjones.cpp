#include <lennardjones.h>
#include <cmath>


MoLennardJones::MoLennardJones(float epsilon, float sigma) :
    epsilon_(epsilon),
    sigma_(sigma)
{}

float MoLennardJones::evaluateAt(float r) const {
    static const float rmin = 1.0e-3f * sigma_;
    float sigmaOverR = sigma_ /
            std::sqrt(r * r + rmin * rmin);
    float xi = sigmaOverR * sigmaOverR;
    xi = xi * xi * xi;
    return 4.0 * epsilon_ * (xi * xi - xi);
}
