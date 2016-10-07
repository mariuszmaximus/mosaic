#ifndef POTENTIALLENNARDJONES_H
#define POTENTIALLENNARDJONES_H

#include <lennardjones.h>
#include <potential.h>

class MoPotentialLennardJones : public MoPotential {
public:
    MoPotentialLennardJones(const MoLennardJones& lennardJones) :
        lennardJones_(lennardJones) {
    }

    virtual ~MoPotentialLennardJones() {}
    virtual float operator()(const float* x1, const float* x2);
private:
    MoLennardJones lennardJones_;
};

#endif // POTENTIALLENNARDJONES_H
