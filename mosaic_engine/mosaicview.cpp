#include <mosaicview.h>

#include <mosaicviewrenderer.h>


MoMosaicView::MoMosaicView() :
renderer_(new MoMosaicViewRenderer) {
}

MoMosaicView::~MoMosaicView() {
    delete renderer_;
}


void MoMosaicView::setModel(std::shared_ptr<MoMosaicModel> model) {
    renderer_->setModel(model);
}

std::shared_ptr<MoMosaicModel> MoMosaicView::getModel() const {
    return renderer_->getModel();
}
