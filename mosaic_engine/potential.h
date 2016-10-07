#ifndef MOPOTENTIAL_H
#define MOPOTENTIAL_H

class MoPotential {
public:
    virtual ~MoPotential() {}
    /**
     * @brief Evaluate the potential between two positions
     * @param x1 First position
     * @param x2 Second position
     * @return The relative interaction potential between x1 and x2.
     */
    virtual float operator()(const float* x1, const float* x2) = 0;
};

#endif // MOPOTENTIAL_H
