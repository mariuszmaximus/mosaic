#include <mosaictargetcorrelation.h>
#include <targetimage.h>
#include <imageutilities.h>
#include <QtGlobal>
#include <QDebug>
#include <QOpenGLFramebufferObject>
#include <mosaicrenderer.h>
#include <QOpenGLFunctions_3_3_Core>


class MoMosaicTargetCorrelationImpl :
        public MoBadness,
        public QOpenGLFunctions_3_3_Core {
public:
    MoMosaicTargetCorrelationImpl(int maxNumTiles) :
        maxNumTiles_(maxNumTiles) {}
    virtual ~MoMosaicTargetCorrelationImpl() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage) {
        static long int i = 0;
        if (i == 0) {
            initGL();
        }

        QOpenGLFramebufferObjectFormat fboFormat;
        fboFormat.setSamples(4);
        fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        QOpenGLFramebufferObject mosaicBuffer(targetImage.getSize(),
                                              fboFormat);
        Q_ASSERT(mosaicBuffer.bind());
        static const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBuffers);

        std::shared_ptr<MoMosaicModel> modelPtr{
            std::make_shared<MoMosaicModel>(model)};
        renderer_.setModel(modelPtr);
        renderer_.render();
        mosaicBuffer.release();
        Q_ASSERT(QOpenGLFramebufferObject::bindDefault());
        QImage mosaicImage{mosaicBuffer.toImage()};
        mosaicImage.save("mosaicImage.png");
        return moDistanceBetweenImages(mosaicImage, targetImage.getImage());
    }

private:
    void initGL() {
        static bool firstCall = true;
        if (firstCall) {
            firstCall = false;
            Q_ASSERT(initializeOpenGLFunctions());
        }
    }

    int maxNumTiles_;
    MoMosaicRenderer renderer_;
};


MoMosaicTargetCorrelation::MoMosaicTargetCorrelation(int maxNumTiles) :
    impl_(new MoMosaicTargetCorrelationImpl(maxNumTiles)) {}

MoMosaicTargetCorrelation::~MoMosaicTargetCorrelation() {}

float MoMosaicTargetCorrelation::computeBadness(const MoMosaicModel &model,
                                              const MoTargetImage &targetImage) {
    return impl_->computeBadness(model, targetImage);
}
