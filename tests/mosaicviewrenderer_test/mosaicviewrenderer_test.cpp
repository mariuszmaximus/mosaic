#include <gtest/gtest.h>
#include <mosaicrenderer.h>
#include <QOffscreenSurface>
#include <QGuiApplication>


TEST(MoMosaicRenderer, CanBeConstructed) {
    MoMosaicRenderer* view = new MoMosaicRenderer;
    ASSERT_NE(view, nullptr);
    delete view;
}

#ifdef leter
TEST(MoMosaicRenderer, PaintDoesNotThrow) {
    MoMosaicRenderer view;
    ASSERT_NO_THROW(view.paint());
}
#endif

TEST(MoMosaicRenderer, CanSetOutlineMode) {
    MoMosaicRenderer view;
    view.setShowOutlines(true);
    ASSERT_TRUE(view.getShowOutlines());
}

TEST(MoMosaicRenderer, CanUnsetOutlineMode) {
    MoMosaicRenderer view;
    view.setShowOutlines(false);
    ASSERT_FALSE(view.getShowOutlines());
}

TEST(MoMosaicRenderer, CanChangeOutlineMode) {
    MoMosaicRenderer view;
    view.setShowOutlines(false);
    ASSERT_FALSE(view.getShowOutlines());
    view.setShowOutlines(true);
    ASSERT_TRUE(view.getShowOutlines());
}

#ifdef leter
TEST(MoMosaicRenderer, SetModel) {
    MoMosaicRenderer view;
    view.setModel(nullptr);
    std::shared_ptr<MoMosaicModel> model = view.getModel();
    ASSERT_EQ(nullptr, model.get());
}
#endif


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
