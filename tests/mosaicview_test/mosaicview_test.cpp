#include <gtest/gtest.h>
#include <mosaicview.h>

TEST(MoMosaicView, CanBeConstructed) {
    MoMosaicView* view = new MoMosaicView;
    ASSERT_NE(view, nullptr);
    delete view;
}
