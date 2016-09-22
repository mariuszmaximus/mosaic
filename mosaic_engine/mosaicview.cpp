#include <mosaicview.h>

#include <mosaicrenderer.h>


MoMosaicView::MoMosaicView() :
    initialized_(false),
    showOutlines_(false),
    showTargetImage_(false),
    magnification_(1.0f) {
    connect(this, &QQuickItem::windowChanged,
            this, &MoMosaicView::handleWindowChanged);
}

MoMosaicView::~MoMosaicView() {}

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
    return getRenderer();
}

void MoMosaicView::setShowOutlines(bool yesNo) {
    showOutlines_ = yesNo;
    if (renderer_) {
        renderer_->setShowOutlines(yesNo);
    }
}

bool MoMosaicView::getShowOutlines() const {
    return showOutlines_;
}

void MoMosaicView::setShowTargetImage(bool yesNo) {
    showTargetImage_ = yesNo;
    if (renderer_) {
        renderer_->setShowTargetImage(yesNo);
    }
}

bool MoMosaicView::getShowTargetImage() const {
    return showTargetImage_;
}

void MoMosaicView::setMagnification(float magnification) {
    magnification_ = magnification;
}

float MoMosaicView::getMagnification() const {
    return magnification_;
}

void MoMosaicView::handleWindowChanged(QQuickWindow *win) {
    if (win) {
        connect(win, &QQuickWindow::sceneGraphInvalidated, this,
                &MoMosaicView::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

MoMosaicRenderer* MoMosaicView::getRenderer() const {
    if (renderer_) {
        return renderer_.get();
    } else {
        // This const_cast is morally ok because creation
        // of the renderer_ is an implementation detail (lazy construction,
        // caching).
        const_cast<MoMosaicView*>(this)->renderer_.reset(new MoMosaicRenderer);
        renderer_->setShowOutlines(showOutlines_);
        renderer_->setShowTargetImage(showTargetImage_);
        return renderer_.get();
    }
}

void MoMosaicView::cleanup() {
    renderer_.reset(nullptr);
}
