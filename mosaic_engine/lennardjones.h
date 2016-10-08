#ifndef LENNARDJONES_H
#define LENNARDJONES_H

class MoLennardJones {
public:
    MoLennardJones(float epsilon, float sigma);
    float evaluateAt(float r) const;
    float epsilon() const {
        return epsilon_;
    }
    float sigma() const {
        return sigma_;
    }
private:
    float epsilon_;
    float sigma_;
};

#endif // LENNARDJONES_H
