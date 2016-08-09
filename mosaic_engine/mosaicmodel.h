#ifndef MOMOSAICMODEL_H
#define MOMOSAICMODEL_H

#include <QImage>
#include <vector>


class MoMosaicModel {
public:
    MoMosaicModel();

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

    void setTargetImage(const QImage& image);

private:
    int size_;
    std::vector<float> widths_;
    std::vector<float> heights_;
    std::vector<float> x_;
    std::vector<float> y_;
    std::vector<float> rotations_;
    std::vector<float> scales_;
    QImage targetImage_;
};

#endif // MOMOSAICMODEL_H
