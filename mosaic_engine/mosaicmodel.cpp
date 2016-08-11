#include "mosaicmodel.h"

#include <stdexcept>


MoMosaicModel::MoMosaicModel() : size_(0) {
}

void MoMosaicModel::resize(int size) {
    size_ = size;
    widths.resize(size);
    heights.resize(size);
    x.resize(size);
    y.resize(size);
    rotations.resize(size);
    scales.resize(size);
}

int MoMosaicModel::size() const {
    return size_;
}

void MoMosaicModel::setWidths(const float *widthsBegin,
                               const float *widthsEnd) {
    if (std::distance(widthsBegin, widthsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [widthsBegin, widthsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(widthsBegin, widthsEnd, widths.begin());
}

void MoMosaicModel::getWidths(float *widthsBegin) const {
    std::copy(widths.cbegin(), widths.cend(), widthsBegin);
}

void MoMosaicModel::setHeights(const float *heightsBegin,
                               const float *heightsEnd) {
    if (std::distance(heightsBegin, heightsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [heightsBegin, heightsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(heightsBegin, heightsEnd, heights.begin());
}

void MoMosaicModel::getHeights(float *heightsBegin) const {
    std::copy(heights.cbegin(), heights.cend(), heightsBegin);
}

void MoMosaicModel::setXCoords(const float *xBegin, const float *xEnd) {
    if (std::distance(xBegin, xEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [xBegin, xEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(xBegin, xEnd, x.begin());
}

void MoMosaicModel::getXCoords(float *xBegin) const {
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

void MoMosaicModel::getYCoords(float *yBegin) const {
    std::copy(y.cbegin(), y.cend(), yBegin);
}

void MoMosaicModel::setRotations(const float *rotationsBegin,
                                 const float *rotationsEnd) {
    if (std::distance(rotationsBegin, rotationsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [rotationsBegin, rotationsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(rotationsBegin, rotationsEnd, rotations.begin());
}

void MoMosaicModel::getRotations(float *rotationsBegin) const {
    std::copy(rotations.cbegin(), rotations.cend(), rotationsBegin);
}

void MoMosaicModel::setScales(const float *scalesBegin,
                              const float *scalesEnd) {
    if (std::distance(scalesBegin, scalesEnd) != size_) {
        throw std::runtime_error(
              "Number of elements in [scalesBegin, scalesEnd) "
              "doesn't match size of MoMosaicModel.");
    }
    std::copy(scalesBegin, scalesEnd, scales.begin());
}

void MoMosaicModel::getScales(float *scalesBegin) const {
    std::copy(scales.cbegin(), scales.cend(), scalesBegin);
}
