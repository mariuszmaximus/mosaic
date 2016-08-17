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
