#ifndef BADNESS_H
#define BADNESS_H


class MoMosaicModel;
class MoTargetImage;


class MoBadness {
public:
    virtual ~MoBadness() {}

    /**
     * @brief Calculate the badness of a mosaic
     * @param model the model
     * @param targetImage the image to be fit by the model
     * @return the badness of the mosaic
     */
    virtual float computeBadness(const MoMosaicModel& model,
                                 const MoTargetImage& targetImage) = 0;
};

#endif // BADNESS_H
