#include <interactiontiletile.h>
#include <mosaicmodel.h>
#include <quadraturerule.h>

#include <QtGlobal>


MoInteractionTileTile::MoInteractionTileTile(
        std::unique_ptr<MoPotential> potential) : potential_(std::move(potential)) {
}

float MoInteractionTileTile::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
  float badness = 0.0f;
  for (int i = 0; i < model.size(); ++i) {
      for (int j = 0; j < i; ++j) {
          badness += computeBadnessPair(model, targetImage, i, j);
      }
  }
  return badness;
}

float MoInteractionTileTile::computeBadnessPair(const MoMosaicModel& model,
                                                const MoTargetImage& targetImage,
                                                int i, int j) {
    Q_UNUSED(model);
    Q_UNUSED(targetImage);
    Q_UNUSED(i);
    Q_UNUSED(j);
    static const int order = 3;
    static const float* weights = &MoQuadratureRule[order][MO_QUADRATURE_WEIGHTS][0];
    static const float* nodes = &MoQuadratureRule[order][MO_QUADRATURE_NODES][0];
    Q_UNUSED(nodes);

    float badness = 0.0f;
    for (int ix = 0; ix < order; ++ix) {
        float b = 0.0f;
        for (int iy = 0; iy < order; ++iy) {
            float bp = 0.0f;
            for (int jx = 0; jx < order; ++jx) {
                float bpp = 0.0f;
                for (int jy = 0; jy < order; ++jy) {
                    bpp += weights[jy] * 1.0f;
                }
                bp += weights[jx] * bpp;
            }
            b += weights[iy] * bp;
        }
        badness += weights[ix] * b;
    }
    return 1.0f;
}
