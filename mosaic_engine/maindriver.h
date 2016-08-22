#ifndef MAINDRIVER_H
#define MAINDRIVER_H

#include <QObject>
#include <QUrl>
#include <vector>
#include <mosaicevolution.h>

class QString;
class QAbstractListModel;
class MoEvolutionRunner;
class MoMosaicModel;


class MoMainDriver : public QObject {
    Q_OBJECT
public:
    explicit MoMainDriver(QObject *parent = 0);
    ~MoMainDriver();

    void setSourceImages(QAbstractListModel* sourceImages);
    std::shared_ptr<MoMosaicModel> getCurrentModel();

public slots:
    void start(QUrl targetUrl);
    void setCurrentModel(std::shared_ptr<MoMosaicModel> newModel);

signals:
    void modelChanged(std::shared_ptr<MoMosaicModel> newModel);

private:
    MoMosaicEvolution evolution_;
    QAbstractListModel* sourceImages_;

    std::vector<QString> getFileNames(
            QAbstractListModel* inputImages) const;

    std::unique_ptr<MoEvolutionRunner> evolutionRunner_;
    std::shared_ptr<MoMosaicModel> currentModel_;
};

#endif // MAINDRIVER_H
