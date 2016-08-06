#ifndef MOMOSAICMODEL_H
#define MOMOSAICMODEL_H

#include <vector>


class MoMosaicModel {
public:
    MoMosaicModel();

    void resize(int size);
    int size() const;

    void setXCoords(const float* xBegin, const float* xEnd);
    void getXCoords(float* xBegin);
    void setYCoords(const float* yBegin, const float* yEnd);
    void getYCoords(float* yBegin);
    void setRotations(const float* rotationsBegin,
                      const float* rotationsEnd);
    void getRotations(float* rotationsBegin);
    void setScales(const float* scalesBegin,
                      const float* scalesEnd);
    void getScales(float* scalesBegin);

private:
    int size_;
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> rotations;
    std::vector<float> scales;
};

#endif // MOMOSAICMODEL_H
