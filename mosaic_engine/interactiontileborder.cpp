#include <interactiontileborder.h>
#include <potential.h>
#include <mosaicmodel.h>
#include <interactionhelpers.h>

#include <QtGlobal>
#include <vector>
#include <cmath>


MoInteractionTileBorder::MoInteractionTileBorder(
        std::unique_ptr<MoPotential> potential) :
    potential_(std::move(potential)) {
}

float MoInteractionTileBorder::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    int numTilesLinear = static_cast<int>(
                std::round(std::sqrt(static_cast<float>(model.size()))));

    const float* x = model.getXCoords();
    const float* y = model.getYCoords();
    std::vector<float> w(model.size());
    model.getWidths(&w[0]);
    std::vector<float> h(model.size());
    model.getHeights(&h[0]);
    const float* alpha = model.getRotations();
    const float* scale = model.getScales();

    float badness = 0.0;
    // bottom row of fake tiles
    QSize targetSize = targetImage.getImage().size();
    // TODO: Check the units on this
    float width0 = static_cast<float>(targetSize.width()) / numTilesLinear;
    float height0 = static_cast<float>(targetSize.height()) / numTilesLinear;
    // TODO check the origin
    for (int i = 0; i != numTilesLinear; ++i) {
        int j = 0;
        float x0 = i * width0 +0.5 * width0;
        float y0 = j * height0 -0.5 * height0;
        for (int ii = 0; ii < model.size(); ++ii) {
            badness +=
                    moComputeBadnessPair(x0, y0, width0, height0, 0.0f, 1.0f,
                                         x[ii], y[ii], w[ii], h[ii], alpha[ii], scale[ii],
                                         potential_.get());
        }
    }
    return badness;
}

void MoInteractionTileBorder::resetPotential(
        std::unique_ptr<MoPotential> potential) {
    potential_ = std::move(potential);
}
