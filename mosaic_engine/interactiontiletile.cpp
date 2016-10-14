#include <interactiontiletile.h>
#include <mosaicmodel.h>
#include <potential.h>
#include <interactionhelpers.h>

#include <QtGlobal>


MoInteractionTileTile::MoInteractionTileTile(
        std::unique_ptr<MoPotential> potential) : potential_(std::move(potential)) {
}

float MoInteractionTileTile::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    Q_UNUSED(targetImage);
    const float* x = model.getXCoords();
    const float* y = model.getYCoords();
    std::vector<float> w(model.size());
    model.getWidths(&w[0]);
    std::vector<float> h(model.size());
    model.getHeights(&h[0]);
    const float* alpha = model.getRotations();
    const float* scale = model.getScales();

    float badness = 0.0f;
    for (int i = 0; i < model.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            badness += moComputeBadnessPair(
                        x[i], y[i], w[i], h[i], alpha[i], scale[i],
                        x[j], y[j], w[j], h[j], alpha[j], scale[j],
                        potential_.get());
        }
    }
    return badness;
}

void MoInteractionTileTile::resetPotential(std::unique_ptr<MoPotential> potential) {
    potential_ = std::move(potential);
}
