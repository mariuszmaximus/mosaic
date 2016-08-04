#include <gtest/gtest.h>
#include <mosaicviewrenderer.h>

TEST(MoMosaicViewRenderer, CanBeConstructed) {
    MoMosaicViewRenderer* view = new MoMosaicViewRenderer;
    ASSERT_NE(view, nullptr);
    delete view;
}

TEST(MoMosaicViewRenderer, PaintDoesNotThrow) {
    MoMosaicViewRenderer view;
    ASSERT_NO_THROW(view.paint());
}
