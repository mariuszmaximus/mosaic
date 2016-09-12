#ifndef LENNARDJONES_H
#define LENNARDJONES_H

class MoLennardJones {
public:
    MoLennardJones(float epsilon, float sigma);
    float evaluateAt(float r) const;
private:
    float epsilon_;
    float sigma_;
};

#endif // LENNARDJONES_H
