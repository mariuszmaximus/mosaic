#ifndef MAINDRIVER_H
#define MAINDRIVER_H

#include <QObject>
#include <QUrl>
#include <vector>
#include <mosaicevolution.h>

class QString;
class QAbstractListModel;
class MoEvolutionRunner;


class MoMainDriver : public QObject {
    Q_OBJECT
public:
    explicit MoMainDriver(QObject *parent = 0);
    ~MoMainDriver();

    void setSourceImages(QAbstractListModel* sourceImages);

public slots:
    void start(QUrl targetUrl);

private:
    MoMosaicEvolution evolution_;
    QAbstractListModel* sourceImages_;

    std::vector<QString> getFileNames(
            QAbstractListModel* inputImages) const;

    std::unique_ptr<MoEvolutionRunner> evolutionRunner_;
};

#endif // MAINDRIVER_H
