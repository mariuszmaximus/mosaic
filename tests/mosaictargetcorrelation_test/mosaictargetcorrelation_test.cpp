#include <gtest/gtest.h>
#include <mosaictargetcorrelation.h>
#include <targetimage.h>
#include <mosaicmodel.h>
#include <test_utilities.h>
#include <QOffscreenSurface>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_3_3_Core>

#include <memory>

static std::unique_ptr<QSurfaceFormat> format;
static std::unique_ptr<QOffscreenSurface> surface;
static std::unique_ptr<QOpenGLContext> context;



TEST(MoMosaicTargetCorrelation, IncludeTest) {
  EXPECT_TRUE(true);
}

TEST(MoMosaicTargetCorrelation, Constructor) {
    std::unique_ptr<MoMosaicTargetCorrelation> ptr;
    EXPECT_NO_THROW(ptr.reset(new MoMosaicTargetCorrelation(10)));
}

struct OpenGLFixture : public ::testing::Test {
    virtual ~OpenGLFixture() {}
    virtual void SetUp() {
        ASSERT_NE(nullptr, context);
        ASSERT_TRUE(context->isValid());
        context->makeCurrent(surface.get());
    }
    virtual void TearDown() {
        context->doneCurrent();
    }
};

TEST_F(OpenGLFixture, CanMakeContextCurrent) {
    //ASSERT_EQ(0u, glGetError());
    EXPECT_TRUE(context->isValid());
    QOpenGLFunctions* funcs =
            QOpenGLContext::currentContext()->functions();
    ASSERT_EQ(0u, funcs->glGetError());
}

TEST_F(OpenGLFixture, CanMakeContextCurrentASecondTime) {
    ASSERT_EQ(0u, glGetError());
    EXPECT_TRUE(context->isValid());
    QOpenGLFunctions* funcs =
            QOpenGLContext::currentContext()->functions();
    ASSERT_EQ(0u, funcs->glGetError());
}

TEST_F(OpenGLFixture, CanInitializeOpenGLFunctions) {
    ASSERT_EQ(0u, glGetError());
    QOpenGLFunctions_3_3_Core funcs;
    EXPECT_TRUE(funcs.initializeOpenGLFunctions());
}

TEST_F(OpenGLFixture, CanInitializeOpenGLFunctionsASecondTime) {
    ASSERT_EQ(0u, glGetError());
    QOpenGLFunctions_3_3_Core funcs;
    EXPECT_TRUE(funcs.initializeOpenGLFunctions());
}

struct MoMosaicTargetCorrelation_Fixture : public OpenGLFixture {
};

TEST_F(MoMosaicTargetCorrelation_Fixture, OfEmptyModelIsZero) {
    MoMosaicTargetCorrelation tileTargetCorrelation(10);
    MoMosaicModel model;
    QImage img{createImage(80, 60)};
    img.fill(QColor(0, 0, 0, 0xFF));
    MoTargetImage targetImage(img, QSize(40, 30));
    EXPECT_FLOAT_EQ(0.0f,
                    tileTargetCorrelation.computeBadness(model, targetImage));
}

TEST_F(MoMosaicTargetCorrelation_Fixture, OfEmptyModelIsZeroAgain) {
    MoMosaicTargetCorrelation tileTargetCorrelation(10);
    MoMosaicModel model;
    QImage img{createImage(80, 60)};
    img.fill(QColor(0, 0, 0, 0xFF));
    MoTargetImage targetImage(img, QSize(40, 30));
    EXPECT_FLOAT_EQ(0.0f,
                    tileTargetCorrelation.computeBadness(model, targetImage));
}

/*
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
    float badness = tileTargetCorrelation.computeBadness(model, targetImage);
    std::cout << badness << std::endl;
    EXPECT_NE(0.0f, badness);
}
*/


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    QGuiApplication app(argc, argv);
    Q_UNUSED(app);


    format.reset(new QSurfaceFormat);
    format->setMajorVersion(3);
    format->setMinorVersion(3);
    format->setProfile(QSurfaceFormat::CoreProfile);
    format->setOptions(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(*format);

    context.reset(new QOpenGLContext);
    context->setFormat(*format);
    context->create();
    if (!context->isValid()) return 1;


    surface.reset(new QOffscreenSurface);
    surface->setFormat(*format);
    surface->create();
    if (!surface->isValid()) return 2;

    context->makeCurrent(surface.get());
    QOpenGLFunctions* funcs = context->functions();
    funcs->initializeOpenGLFunctions();

    QOpenGLDebugLogger logger;
    logger.initialize();
    DebugMessageHandler handler;
    handler.connectToLogger(&logger);

    int result = RUN_ALL_TESTS();

    context->doneCurrent();
    format.release();
    surface.release();
    context.release();

    return result;
}
