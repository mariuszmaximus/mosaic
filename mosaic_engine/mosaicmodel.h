#ifndef MOMOSAICMODEL_H
#define MOMOSAICMODEL_H

#include <vector>

class MoTargetImage;
class MoTile;


class MoMosaicModel {
public:
    MoMosaicModel();

    void constructInitialState(const MoTargetImage& targetImage,
                               const std::vector<MoTile>& tiles);

    void resize(int size);
    int size() const;

    void setWidths(const float* widthsBegin,
                   const float* widthsEnd);
    void getWidths(float* widthsBegin) const;

    void setHeights(const float* heightsBegin,
                    const float* heightsEnd);
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
    std::vector<float> widths;
    std::vector<float> heights;
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> rotations;
    std::vector<float> scales;
};

#endif // MOMOSAICMODEL_H
