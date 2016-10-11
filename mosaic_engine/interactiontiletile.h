#ifndef INTERACTIONTILETILE_H
#define INTERACTIONTILETILE_H

#include <badness.h>
#include <memory>

class MoPotential;


class MoInteractionTileTile : public MoBadness {
public:
    MoInteractionTileTile(std::unique_ptr<MoPotential> potential);
    virtual ~MoInteractionTileTile() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage);
    void resetPotential(std::unique_ptr<MoPotential> potential);
private:
    std::unique_ptr<MoPotential> potential_;
};

#endif // INTERACTIONTILETILE_H
