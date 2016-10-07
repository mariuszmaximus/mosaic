#include <interactiontiletile.h>

#include <QtGlobal>


MoInteractionTileTile::MoInteractionTileTile(
        std::unique_ptr<MoPotential> potential) : potential_(std::move(potential)) {
}

float MoInteractionTileTile::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    Q_UNUSED(model);
    Q_UNUSED(targetImage);
    return 0.0f;
}
