#include <gtest/gtest.h>
#include <mosaicviewrenderer.h>
#include <QOffscreenSurface>


TEST(MoMosaicViewRenderer, CanBeConstructed) {
    MoMosaicViewRenderer* view = new MoMosaicViewRenderer;
    ASSERT_NE(view, nullptr);
    delete view;
}

TEST(MoMosaicViewRenderer, PaintDoesNotThrow) {
    MoMosaicViewRenderer view;
    ASSERT_NO_THROW(view.paint());
}

TEST(MoMosaicViewRenderer, CanInitializeGL) {
    MoMosaicViewRenderer view;
    QOpenGLContext context;
    context.create();
    QOffscreenSurface surface;
    surface.create();
    context.makeCurrent(&surface);
    ASSERT_NO_THROW(view.initGL());
}
