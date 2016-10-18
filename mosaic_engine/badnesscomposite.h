#ifndef BADNESSCOMPOSITE_H
#define BADNESSCOMPOSITE_H

#include <badness.h>

#include <memory>
#include <vector>


class MoBadnessComposite : public MoBadness {
public:
    virtual ~MoBadnessComposite() {}
    virtual float computeBadness(
            const MoMosaicModel &model, const MoTargetImage &targetImage);
    void addBadness(std::unique_ptr<MoBadness> badness);

private:
    std::vector<std::unique_ptr<MoBadness> > badnesses_;
};

#endif // BADNESSCOMPOSITE_H
