#ifndef MOMOSAICMODEL_H
#define MOMOSAICMODEL_H

#include <vector>

#include <targetimage.h>
#include <tile.h>


class MoMosaicModel {
public:
    MoMosaicModel();

    void constructInitialState(const MoTargetImage& targetImage,
                               const std::vector<MoTile>& tiles);

    void resize(int size);
    int size() const;

    void getWidths(float* widthsBegin) const;
    void getHeights(float* heightsBegin) const;

    void setXCoords(const float* xBegin, const float* xEnd);
    void getXCoords(float* xBegin) const;

    void setYCoords(const float* yBegin, const float* yEnd);
    void getYCoords(float* yBegin) const;

    void setRotations(const float* rotationsBegin,
                      const float* rotationsEnd);
    void getRotations(float* rotationsBegin) const;

    void setScales(const float* scalesBegin,
                      const float* scalesEnd);
    void getScales(float* scalesBegin) const;

private:
    int size_;
    std::vector<float> x_;
    std::vector<float> y_;
    std::vector<float> rotations_;
    std::vector<float> scales_;
    MoTargetImage targetImage_;
    std::vector<MoTile> tiles_;
};

#endif // MOMOSAICMODEL_H
