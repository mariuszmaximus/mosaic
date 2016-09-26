#ifndef MOMOSAICMODEL_H
#define MOMOSAICMODEL_H

#include <vector>

#include <targetimage.h>
#include <tile.h>


class MoMosaicModel {
public:
    MoMosaicModel();
    MoMosaicModel(const MoMosaicModel&) = default;
    MoMosaicModel& operator=(const MoMosaicModel&) = default;
    MoMosaicModel(MoMosaicModel&&) = default;
    MoMosaicModel& operator=(MoMosaicModel&&) = default;
    ~MoMosaicModel() {}

    void constructInitialState(const MoTargetImage& targetImage,
                               const std::vector<MoTile>& tiles);

    void resize(int size);
    int size() const;

    void getWidths(float* widthsBegin) const;
    void getHeights(float* heightsBegin) const;

    void setXCoords(const float* xBegin, const float* xEnd);
    float* getXCoords();
    const float* getXCoords() const;
    void copyXCoords(float* xBegin) const;

    void setYCoords(const float* yBegin, const float* yEnd);
    float* getYCoords();
    const float* getYCoords() const;
    void copyYCoords(float* yBegin) const;

    void setRotations(const float* rotationsBegin,
                      const float* rotationsEnd);
    float* getRotations();
    const float* getRotations() const;
    void copyRotations(float* rotationsBegin) const;

    void setScales(const float* scalesBegin,
                      const float* scalesEnd);
    float* getScales();
    const float* getScales() const;
    void copyScales(float* scalesBegin) const;

    const MoTargetImage& getTargetImage() const;
    const std::vector<MoTile>& getTiles() const;

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
