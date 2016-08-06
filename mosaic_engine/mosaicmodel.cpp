#include "mosaicmodel.h"

#include <stdexcept>


MoMosaicModel::MoMosaicModel() : size_(0) {
}

void MoMosaicModel::resize(int size) {
    size_ = size;
    x.resize(size);
    y.resize(size);
}

int MoMosaicModel::size() const {
    return size_;
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

void MoMosaicModel::setYCoords(const float *yBegin, const float *yEnd) {
    if (std::distance(yBegin, yEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [yBegin, yEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(yBegin, yEnd, y.begin());
}

void MoMosaicModel::getYCoords(float *yBegin) {
    std::copy(y.cbegin(), y.cend(), yBegin);
}
