#include <mosaicview.h>

#include <mosaicrenderer.h>


MoMosaicView::MoMosaicView() :
    renderer_(new MoMosaicRenderer) {
    connect(this, &QQuickItem::windowChanged,
            this, &MoMosaicView::handleWindowChanged);
}

MoMosaicView::~MoMosaicView() {
}

void MoMosaicView::setModel(std::shared_ptr<MoMosaicModel> model) {
    renderer_->setModel(model);
    this->update();
}

std::shared_ptr<MoMosaicModel> MoMosaicView::getModel() const {
    std::shared_ptr<MoMosaicModel> theModel =
            std::make_shared<MoMosaicModel>(renderer_->getModel());
    return theModel;
}

QQuickFramebufferObject::Renderer *MoMosaicView::createRenderer() const {
    return new MoMosaicRenderer;
}

void MoMosaicView::handleWindowChanged(QQuickWindow *win) {
    if (win) {
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &MoMosaicView::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void MoMosaicView::cleanup() {
    renderer_.reset(nullptr);
}
