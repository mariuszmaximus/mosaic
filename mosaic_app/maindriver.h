#ifndef MAINDRIVER_H
#define MAINDRIVER_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>
#include <vector>
#include <string>


class MoMainDriver : public QObject
{
    Q_OBJECT
public:
    explicit MoMainDriver(QObject *parent = 0);

public slots:
    void start(QAbstractListModel* inputImages, QUrl targetUrl);
private:
    std::vector<std::string> getFileNames(
            QAbstractListModel* inputImages) const;
};

#endif // MAINDRIVER_H
