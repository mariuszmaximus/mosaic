#include <mosaicupdateoptimize.h>
#include <badness.h>
#include <mosaicmodel.h>

#include <QtGlobal>
#include <QDebug>


void MoMosaicUpdateOptimize::update(MoMosaicModel *model) {
    float b = badness_->computeBadness(*model, model->getTargetImage());
    qDebug() << "badness == " << b;
}

void MoMosaicUpdateOptimize::setBadness(std::unique_ptr<MoBadness> badness) {
    badness_ = std::move(badness);
}
