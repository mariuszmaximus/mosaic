#ifndef BADNESSCOMPOSITE_H
#define BADNESSCOMPOSITE_H

#include <badness.h>


class MoBadnessComposite : public MoBadness {
public:
    virtual ~MoBadnessComposite() {}
    virtual float computeBadness(
            const MoMosaicModel &model, const MoTargetImage &targetImage);
};

#endif // BADNESSCOMPOSITE_H
