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

    Q_PROPERTY(QUrl targetURL MEMBER targetUrl_ READ getTargetURL WRITE setTargetURL NOTIFY targetURLChanged)
public:
    explicit MoMainDriver(QObject *parent = 0);
    ~MoMainDriver();

    void setSourceImages(QAbstractListModel* sourceImages);
    std::shared_ptr<MoMosaicModel> getCurrentModel();

public slots:
    void stop();
    void start();
    void setCurrentModel(std::shared_ptr<MoMosaicModel> newModel);
    void setTargetURL(QUrl targetUrl);
    QUrl getTargetURL();

signals:
    void modelChanged(std::shared_ptr<MoMosaicModel> newModel);
    void targetURLChanged(QUrl newURL);

private:
    MoMosaicEvolution evolution_;
    QAbstractListModel* sourceImages_;
    QUrl targetUrl_;

    std::unique_ptr<MoEvolutionRunner> evolutionRunner_;
    std::shared_ptr<MoMosaicModel> currentModel_;

    // Some helper functions
    std::vector<QString> getFileNames(
            QAbstractListModel* inputImages) const;
    void shutDownEvolutionRunner();
};

#endif // MAINDRIVER_H
