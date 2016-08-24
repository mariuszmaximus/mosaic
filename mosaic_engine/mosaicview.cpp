#include <mosaicview.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicView::MoMosaicView() :
    renderer_(0) {
    connect(this, &QQuickItem::windowChanged,
            this, &MoMosaicView::handleWindowChanged);
}

MoMosaicView::~MoMosaicView() {
    delete renderer_;
}


void MoMosaicView::setModel(std::shared_ptr<MoMosaicModel> model) {
    qDebug() << "In MoMosaicView::setModel.";
    renderer_->setModel(model);
}

std::shared_ptr<MoMosaicModel> MoMosaicView::getModel() const {
    return renderer_->getModel();
}

void MoMosaicView::handleWindowChanged(QQuickWindow *win) {
     if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &MoMosaicView::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &MoMosaicView::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
   qDebug() << "in MoMosaicView::handleWindowChanged";
}

void MoMosaicView::sync() {
    if (!renderer_) {
        renderer_ = new MoMosaicViewRenderer;
        connect(window(), &QQuickWindow::beforeRendering, renderer_,
                &MoMosaicViewRenderer::paint, Qt::DirectConnection);
    }
    renderer_->setViewportSize(window()->size() * window()->devicePixelRatio());
    renderer_->setWindow(window());
}

void MoMosaicView::cleanup() {
    if (renderer_) {
        delete renderer_;
        renderer_ = 0;
    }
}
