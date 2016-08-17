#include "mosaicevolution.h"

#include <vector>

#include <mosaicmodel.h>
#include <mosaicupdate.h>


class MoMosaicEvolution::MoMosaicEvolutionImpl {
public:
    MoMosaicEvolutionImpl() : model_() {}

    MoMosaicModel* getCurrentModel() {
        return &model_;
    }

    void takeStep() {
    }

    void addUpdate(std::unique_ptr<MoMosaicUpdate>&& update) {
        updates_.emplace_back(std::move(update));
    }

    void constructInitialState(
            const MoTargetImage& targetImage,
            const std::vector<MoTile>& tiles) {
        model_.constructInitialState(targetImage, tiles);
    }

private:
    MoMosaicModel model_;
    std::vector<std::unique_ptr<MoMosaicUpdate> > updates_;
};

MoMosaicEvolution::MoMosaicEvolution() :
    impl_(new MoMosaicEvolutionImpl) {
}

MoMosaicEvolution::~MoMosaicEvolution() {
}

MoMosaicModel* MoMosaicEvolution::getCurrentModel() {
    return impl_->getCurrentModel();
}

void MoMosaicEvolution::takeStep() {
    impl_->takeStep();
}

void MoMosaicEvolution::addUpdate(std::unique_ptr<MoMosaicUpdate>&& update) {
    impl_->addUpdate(std::move(update));
}

void MoMosaicEvolution::constructInitialState(
        const MoTargetImage& targetImage,
        const std::vector<MoTile>& tiles) {
    impl_->constructInitialState(targetImage, tiles);
}
