#ifndef MAINDRIVER_H
#define MAINDRIVER_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>
#include <vector>
#include <string>

#include <mosaicmodel.h>


class MoMainDriver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl targetImage WRITE setTargetImage NOTIFY targetImageChanged)
public:
    explicit MoMainDriver(QObject *parent = 0);
    void setTargetImage(const QUrl& newTarget);
    void targetImageChanged();

public slots:
    void start(QAbstractListModel* inputImages, QUrl targetUrl);

private:
    MoMosaicModel mosaicModel_;

    std::vector<std::string> getFileNames(
            QAbstractListModel* inputImages) const;
};

#endif // MAINDRIVER_H
