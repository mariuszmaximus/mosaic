#include <badnesscomposite.h>
#include <QtGlobal>

float MoBadnessComposite::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    float badness = 0.0f;
    for (auto& b : badnesses_) {
        badness += b->computeBadness(model, targetImage);
    }
    return badness;
}

void MoBadnessComposite::addBadness(std::unique_ptr<MoBadness> badness) {
    badnesses_.emplace_back(std::move(badness));
}
