#include <interactiontiletile.h>
#include <mosaicmodel.h>

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
    return 1.0f;
}
