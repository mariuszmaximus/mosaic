#ifndef TILETARGETCORRELATION_H
#define TILETARGETCORRELATION_H

#include <badness.h>
#include <memory>


class MoMosaicTargetCorrelationImpl;


class MoMosaicTargetCorrelation : public MoBadness {
public:
    MoMosaicTargetCorrelation(int maxNumTiles);
    virtual ~MoMosaicTargetCorrelation();
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage);
private:
    std::unique_ptr<MoMosaicTargetCorrelationImpl> impl_;
};


#endif // TILETARGETCORRELATION_H
