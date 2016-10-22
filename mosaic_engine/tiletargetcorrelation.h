#ifndef TILETARGETCORRELATION_H
#define TILETARGETCORRELATION_H

#include <badness.h>
#include <QtGlobal>


class MoTileTargetCorrelation : public MoBadness {
public:
    MoTileTargetCorrelation(int maxNumTiles) {
        Q_UNUSED(maxNumTiles);
    }
    virtual ~MoTileTargetCorrelation() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage);

};


#endif // TILETARGETCORRELATION_H
