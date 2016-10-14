#ifndef INTERACTIONTILEBORDER_H
#define INTERACTIONTILEBORDER_H

#include <badness.h>
#include <memory>

class MoPotential;


class MoInteractionTileBorder : public MoBadness {
public:
    MoInteractionTileBorder(std::unique_ptr<MoPotential> potential);
    virtual ~MoInteractionTileBorder() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage);
    void resetPotential(std::unique_ptr<MoPotential> potential);
private:
    std::unique_ptr<MoPotential> potential_;
};

#endif // INTERACTIONTILEBORDER_H
