#ifndef SOURCEIMAGES_H
#define SOURCEIMAGES_H

#include <QObject>
#include <QVariant>
#include <QAbstractListModel>
#include <QVector>
#include <QUrl>
#include <QImage>
#include <QByteArray>
#include <QHash>
#include <thumbnail.h>


class MoSourceImages : public QAbstractListModel
{
    Q_OBJECT
public:
    MoSourceImages(QObject* parent = 0);

    enum DataRoles {
        FileNameRole = Qt::UserRole + 1,
        ImageRole,
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QImage getImage(const QString& id) const;

    QHash<int, QByteArray> roleNames() const;

public slots:
    void imagesAdded(const QList<QUrl>& newImages);

signals:
    void dataChanged();

private:
    QVector<MoThumbnail> thumbnails_;
};

#endif // SOURCEIMAGES_H
