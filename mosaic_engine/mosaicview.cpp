#include <mosaicview.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicView::MoMosaicView() :
    renderer_(new MoMosaicViewRenderer) {
    connect(this, &QQuickItem::windowChanged,
            this, &MoMosaicView::handleWindowChanged);
}

MoMosaicView::~MoMosaicView() {
}


void MoMosaicView::setModel(std::shared_ptr<MoMosaicModel> model) {
    qDebug() << "In MoMosaicView::setModel.";
    renderer_->setModel(model);
}

std::shared_ptr<MoMosaicModel> MoMosaicView::getModel() const {
    return renderer_->getModel();
}

QQuickFramebufferObject::Renderer *MoMosaicView::createRenderer() const {
    return new MoMosaicViewRenderer;
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
    qDebug() << "in MoMosaicView::sync";
    renderer_->setViewportSize(window()->size() * window()->devicePixelRatio());
    renderer_->setWindow(window());
}

void MoMosaicView::cleanup() {
    renderer_.reset(nullptr);
}
