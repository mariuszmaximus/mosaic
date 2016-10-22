#include <gtest/gtest.h>
#include <mosaictargetcorrelation.h>
#include <targetimage.h>
#include <mosaicmodel.h>
#include <test_utilities.h>
#include <QOffscreenSurface>
#include <QGuiApplication>
#include <QOpenGLContext>

#include <memory>


TEST(MoMosaicTargetCorrelation, IncludeTest) {
  EXPECT_TRUE(true);
}

TEST(MoMosaicTargetCorrelation, Constructor) {
    std::unique_ptr<MoMosaicTargetCorrelation> ptr;
    EXPECT_NO_THROW(ptr.reset(new MoMosaicTargetCorrelation(10)));
}

TEST(MoMosaicTargetCorrelation, OfEmptyModelIsZero) {
    MoMosaicTargetCorrelation tileTargetCorrelation(10);
    MoMosaicModel model;
    MoTargetImage targetImage(QImage(), QSize(40, 30));
    EXPECT_FLOAT_EQ(0.0f,
                    tileTargetCorrelation.computeBadness(model, targetImage));
}

static MoMosaicModel createSomeModel(const MoTargetImage& targetImage,
                                     int numTiles) {
    MoMosaicModel model;
    std::vector<MoTile> tiles(numTiles,
                              MoTile(QImage(20, 30, QImage::Format_RGBA8888)));
    model.constructInitialState(targetImage, tiles);
    std::vector<float> x(numTiles);
    model.setXCoords(&x[0], &x[0] + numTiles);
    std::vector<float> y(numTiles);
    model.setXCoords(&y[0], &y[0] + numTiles);
    std::vector<float> rotations(numTiles, 0.0f);
    model.setRotations(&rotations[0], &rotations[0] + numTiles);
    std::vector<float> scales(numTiles, 1.0f);
    model.setScales(&scales[0], &scales[0] + numTiles);
    return model;
}

TEST(MoMosaicTargetCorrelation, OfNonEmptyModelIsNonZero) {
    MoMosaicTargetCorrelation tileTargetCorrelation(10);
    MoTargetImage targetImage(createImage(120, 80), QSize(120, 80));
    MoMosaicModel model{createSomeModel(targetImage, 3)};
    EXPECT_NE(0.0f, tileTargetCorrelation.computeBadness(model, targetImage));
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

    QOffscreenSurface surface;
    surface.setFormat(format);
    surface.create();
    if(!surface.isValid()) return 2;

    context.makeCurrent(&surface);

    return RUN_ALL_TESTS();
}
