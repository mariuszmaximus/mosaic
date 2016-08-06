#include <gtest/gtest.h>
#include <mosaicviewrenderer.h>
#include <QOffscreenSurface>
#include <QGuiApplication>


TEST(MoMosaicViewRenderer, CanBeConstructed) {
    MoMosaicViewRenderer* view = new MoMosaicViewRenderer;
    ASSERT_NE(view, nullptr);
    delete view;
}

TEST(MoMosaicViewRenderer, PaintDoesNotThrow) {
    MoMosaicViewRenderer view;
    ASSERT_NO_THROW(view.paint());
}

TEST(MoMosaicViewRenderer, CanSetOutlineMode) {
    MoMosaicViewRenderer view;
    view.setShowOutlines(true);
    ASSERT_TRUE(view.showOutlines());
}

TEST(MoMosaicViewRenderer, CanUnsetOutlineMode) {
    MoMosaicViewRenderer view;
    view.setShowOutlines(false);
    ASSERT_FALSE(view.showOutlines());
}

TEST(MoMosaicViewRenderer, CanChangeOutlineMode) {
    MoMosaicViewRenderer view;
    view.setShowOutlines(false);
    ASSERT_FALSE(view.showOutlines());
    view.setShowOutlines(true);
    ASSERT_TRUE(view.showOutlines());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    QGuiApplication app(argc, argv);
    Q_UNUSED(app);

    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(0);

    QOpenGLContext context;
    context.setFormat(format);
    context.create();
    if (!context.isValid()) return 1;
    qDebug() << QString::fromLatin1("Context created.");

    QOffscreenSurface surface;
    surface.setFormat(format);
    surface.create();
    if(!surface.isValid()) return 2;
    qDebug() << QString::fromLatin1("Surface created.");

    context.makeCurrent(&surface);

    return RUN_ALL_TESTS();
}
