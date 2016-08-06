#include "mosaicmodel.h"

#include <stdexcept>


MoMosaicModel::MoMosaicModel() : size_(0) {
}

void MoMosaicModel::resize(int size) {
    size_ = size;
    x.resize(size);
}

void MoMosaicModel::setXCoords(const float *xBegin, const float *xEnd) {
    if (std::distance(xBegin, xEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [xBegin, xEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(xBegin, xEnd, x.begin());
}

void MoMosaicModel::getXCoords(float *xBegin) {
    std::copy(x.cbegin(), x.cend(), xBegin);
}
