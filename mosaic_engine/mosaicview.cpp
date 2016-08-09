#include <mosaicview.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicView::MoMosaicView() :
    QQuickImageProvider(QQuickImageProvider::Image),
    renderer_(0) {
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
