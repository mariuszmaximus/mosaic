#include "mosaicupdatedelay.h"
#include <QThread>


MoMosaicUpdateDelay::MoMosaicUpdateDelay(unsigned long int delayInMS) :
    delay_(delayInMS) {
}

MoMosaicUpdateDelay::~MoMosaicUpdateDelay() {
}

void MoMosaicUpdateDelay::update(MoMosaicModel *model) {
    Q_UNUSED(model);
    QThread::msleep(delay_);
}
