#include "evolutionrunner.h"
#include <mosaicevolution.h>
#include <mosaicmodel.h>
#include <QDebug>


MoEvolutionRunner::MoEvolutionRunner(QObject* parent) :
    QThread(parent),
    evolution_(0),
    notificationPeriod_(1000) {
    qRegisterMetaType<std::shared_ptr<MoMosaicModel> >();
}

MoEvolutionRunner::~MoEvolutionRunner() {}

void MoEvolutionRunner::setEvolution(MoMosaicEvolution* evolution) {
    evolution_ = evolution;
}

void MoEvolutionRunner::run() {
    int i = 0;
    while (1) {
        if (i % notificationPeriod_ == 0) {
            qDebug() << " i == " << i;
            std::shared_ptr<MoMosaicModel> currentModel =
                    std::make_shared<MoMosaicModel>(
                        *evolution_->getCurrentModel());
            emit modelChanged(currentModel);
        }
        evolution_->takeStep();
        ++i;
    }
}

int MoEvolutionRunner::getNotificationPeriod() const {
    return notificationPeriod_;
}

void MoEvolutionRunner::setNotificationPeriod(int period) {
   notificationPeriod_ = period;
}
