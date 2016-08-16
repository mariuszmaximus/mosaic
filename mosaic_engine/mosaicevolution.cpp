#include "mosaicevolution.h"

#include <vector>

#include <mosaicmodel.h>
#include <mosaicupdate.h>


class MoMosaicEvolution::MoMosaicEvolutionImpl {
public:
    MoMosaicEvolutionImpl() : model_() {}
    MoMosaicModel* getCurrentModel() {
        return model_.get();
    }

private:
    std::unique_ptr<MoMosaicModel> model_;
    std::vector<std::unique_ptr<MoMosaicUpdate> > updates_;
};

MoMosaicEvolution::MoMosaicEvolution() {
}

MoMosaicEvolution::~MoMosaicEvolution() {
}

MoMosaicModel* MoMosaicEvolution::getCurrentModel() {
    return impl_->getCurrentModel();
}
