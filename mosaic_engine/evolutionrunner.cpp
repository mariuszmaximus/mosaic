#include "evolutionrunner.h"
#include <mosaicevolution.h>
#include <mosaicmodel.h>
#include <QDebug>


MoEvolutionRunner::MoEvolutionRunner(QObject* parent) :
        QThread(parent),
        evolution_(0) {
    }

MoEvolutionRunner::~MoEvolutionRunner() {}

void MoEvolutionRunner::setEvolution(MoMosaicEvolution* evolution) {
    evolution_ = evolution;
}

void MoEvolutionRunner::run() {
    qDebug() << "in runner.run().";
    int i = 0;
    while (1) {
        qDebug() << "Taking step" << i;
        evolution_->takeStep();
        ++i;
    }
}
