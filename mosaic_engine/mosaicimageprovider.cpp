#include <mosaicimageprovider.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicImageProvider::MoMosaicImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image),
    renderer_(0) {
}

MoMosaicImageProvider::~MoMosaicImageProvider() {
    delete renderer_;
}


void MoMosaicImageProvider::setModel(std::shared_ptr<MoMosaicModel> model) {
    renderer_->setModel(model);
}

std::shared_ptr<MoMosaicModel> MoMosaicImageProvider::getModel() const {
    return renderer_->getModel();
}
