#include "mosaicmodel.h"

#include <stdexcept>


MoMosaicModel::MoMosaicModel() : size_(0) {
}

void MoMosaicModel::resize(int size) {
    size_ = size;
    widths_.resize(size);
    heights_.resize(size);
    x_.resize(size);
    y_.resize(size);
    rotations_.resize(size);
    scales_.resize(size);
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
    std::copy(widthsBegin, widthsEnd, widths_.begin());
}

void MoMosaicModel::getWidths(float *widthsBegin) const {
    std::copy(widths_.cbegin(), widths_.cend(), widthsBegin);
}

void MoMosaicModel::setHeights(const float *heightsBegin,
                               const float *heightsEnd) {
    if (std::distance(heightsBegin, heightsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [heightsBegin, heightsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(heightsBegin, heightsEnd, heights_.begin());
}

void MoMosaicModel::getHeights(float *heightsBegin) const {
    std::copy(heights_.cbegin(), heights_.cend(), heightsBegin);
}

void MoMosaicModel::setXCoords(const float *xBegin, const float *xEnd) {
    if (std::distance(xBegin, xEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [xBegin, xEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(xBegin, xEnd, x_.begin());
}

void MoMosaicModel::getXCoords(float *xBegin) const {
    std::copy(x_.cbegin(), x_.cend(), xBegin);
}


void MoMosaicModel::setYCoords(const float *yBegin, const float *yEnd) {
    if (std::distance(yBegin, yEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [yBegin, yEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(yBegin, yEnd, y_.begin());
}

void MoMosaicModel::getYCoords(float *yBegin) const {
    std::copy(y_.cbegin(), y_.cend(), yBegin);
}

void MoMosaicModel::setRotations(const float *rotationsBegin,
                                 const float *rotationsEnd) {
    if (std::distance(rotationsBegin, rotationsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [rotationsBegin, rotationsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(rotationsBegin, rotationsEnd, rotations_.begin());
}

void MoMosaicModel::getRotations(float *rotationsBegin) const {
    std::copy(rotations_.cbegin(), rotations_.cend(), rotationsBegin);
}

void MoMosaicModel::setScales(const float *scalesBegin,
                              const float *scalesEnd) {
    if (std::distance(scalesBegin, scalesEnd) != size_) {
        throw std::runtime_error(
              "Number of elements in [scalesBegin, scalesEnd) "
              "doesn't match size of MoMosaicModel.");
    }
    std::copy(scalesBegin, scalesEnd, scales_.begin());
}

void MoMosaicModel::getScales(float *scalesBegin) const {
    std::copy(scales_.cbegin(), scales_.cend(), scalesBegin);
}

void MoMosaicModel::setTargetImage(const QImage& image) {
    targetImage_ = image;
}
