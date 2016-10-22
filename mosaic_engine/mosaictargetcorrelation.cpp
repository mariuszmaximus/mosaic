#include <mosaictargetcorrelation.h>
#include <QtGlobal>
#include <QOpenGLFramebufferObject>


class MoMosaicTargetCorrelationImpl : public MoBadness {
public:
    MoMosaicTargetCorrelationImpl(int maxNumTiles) :
        maxNumTiles_(maxNumTiles) {}
    virtual ~MoMosaicTargetCorrelationImpl() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage) {
        Q_UNUSED(model);
        Q_UNUSED(targetImage);
        QOpenGLFramebufferObject mosaicBuffer(targetImage.size());
        Q_UNUSED(mosaicBuffer);

        QImage mosaicImage{mosaicBuffer.toImage()};
        return 0.0f;
    }
private:
    int maxNumTiles_;
};


MoMosaicTargetCorrelation::MoMosaicTargetCorrelation(int maxNumTiles) :
    impl_(new MoMosaicTargetCorrelationImpl(maxNumTiles)) {}

MoMosaicTargetCorrelation::~MoMosaicTargetCorrelation() {}

float MoMosaicTargetCorrelation::computeBadness(const MoMosaicModel &model,
                                              const MoTargetImage &targetImage) {
    return impl_->computeBadness(model, targetImage);
}
