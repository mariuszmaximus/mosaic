#ifndef MOEVOLUTIONRUNNER_H
#define MOEVOLUTIONRUNNER_H

#include <QObject>
#include <QThread>
#include <memory>


class MoMosaicEvolution;
class MoMosaicModel;


class MoEvolutionRunner : public QThread {
    Q_OBJECT
public:
    explicit MoEvolutionRunner(QObject* parent = 0);
    virtual ~MoEvolutionRunner();

    void setEvolution(MoMosaicEvolution* evolution);
    virtual void run();

signals:
    void modelChanged(std::shared_ptr<MoMosaicModel> newModel);

private:
    MoMosaicEvolution* evolution_;
};



#endif // MOEVOLUTIONRUNNER_H
