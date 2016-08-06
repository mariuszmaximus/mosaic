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

private:
    int size_;
    std::vector<float> x;
    std::vector<float> y;
};

#endif // MOMOSAICMODEL_H
