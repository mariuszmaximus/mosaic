#include <gtest/gtest.h>
#include <mosaicview.h>

TEST(MosaicView, CanBeConstructed) {
    MoMosaicView* view = new MoMosaicView;
    ASSERT_NE(view, nullptr);
    delete view;
}
