#ifndef MOEVOLUTIONRUNNER_H
#define MOEVOLUTIONRUNNER_H

#include <QObject>
#include <QThread>
#include <memory>


class MoMosaicEvolution;
class MoMosaicModel;

Q_DECLARE_METATYPE(std::shared_ptr<MoMosaicModel>)


class MoEvolutionRunner : public QThread {
    Q_OBJECT
public:
    explicit MoEvolutionRunner(QObject* parent = 0);
    virtual ~MoEvolutionRunner();

    void setEvolution(MoMosaicEvolution* evolution);
    virtual void run();

    void setNotificationPeriod(int period);
    int getNotificationPeriod() const;

public slots:
    void pause();

signals:
    void modelChanged(std::shared_ptr<MoMosaicModel> newModel);

private:
    MoMosaicEvolution* evolution_;
    int running_;
    int notificationPeriod_;
};

#endif // MOEVOLUTIONRUNNER_H
