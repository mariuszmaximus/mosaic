#ifndef MAINDRIVER_H
#define MAINDRIVER_H

#include <QObject>
#include <QUrl>
#include <vector>
#include <mosaicevolution.h>

class QString;
class QAbstractListModel;


class MoMainDriver : public QObject {
    Q_OBJECT
public:
    explicit MoMainDriver(QObject *parent = 0);

public slots:
    void start(QAbstractListModel* inputImages, QUrl targetUrl);

private:
    MoMosaicEvolution evolution_;

    std::vector<QString> getFileNames(
            QAbstractListModel* inputImages) const;
};

#endif // MAINDRIVER_H
