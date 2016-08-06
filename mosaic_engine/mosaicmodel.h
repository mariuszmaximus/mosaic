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

private:
    int size_;
    std::vector<float> x;
};

#endif // MOMOSAICMODEL_H
