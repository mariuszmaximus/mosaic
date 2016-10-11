#include <interactiontileborder.h>
#include <potential.h>
#include <QtGlobal>


MoInteractionTileBorder::MoInteractionTileBorder(
        std::unique_ptr<MoPotential> potential) :
    potential_(std::move(potential)) {
}

float MoInteractionTileBorder::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    Q_UNUSED(model);
    Q_UNUSED(targetImage);
    return 0.0f;
}

void MoInteractionTileBorder::resetPotential(
        std::unique_ptr<MoPotential> potential) {
    potential_ = std::move(potential);
}
