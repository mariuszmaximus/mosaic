#include "sourceimages.h"
#include <QDebug>
#include <iostream>


MoSourceImages::MoSourceImages(QObject* parent) :
    QAbstractListModel(parent)
{
}

int MoSourceImages::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return thumbnails_.size();
}

QVariant MoSourceImages::data(const QModelIndex &index, int role) const
{
    QVariant result;
    switch(role) {
    case ImageRole:
        result =  thumbnails_[index.row()].getImage();
        break;
    case FileNameRole:
        result = thumbnails_[index.row()].getUrl();
        break;
    default:
        qDebug() << "Unknown role.";
        break;
    }
    return result;
}

QImage MoSourceImages::getImage(const QString &id) const
{
    return thumbnails_[id.toInt()].getImage();
}

void MoSourceImages::imagesAdded(const QList<QUrl>& newImages)
{
    std::cout << "HERE" << std::endl;
    std::cout << newImages.size() << std::endl;
  if (newImages.empty()) {
    return;
  }
  beginInsertRows(QModelIndex(), thumbnails_.size(), thumbnails_.size() + newImages.size() - 1);
  for (QList<QUrl>::const_iterator url = newImages.cbegin();
       url != newImages.cend(); ++url) {
    thumbnails_ << MoThumbnail(QImage(url->toLocalFile()), *url);
  }
  endInsertRows();
  emit dataChanged();
}

QHash<int, QByteArray> MoSourceImages::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[FileNameRole] = "filename";
  roles[ImageRole] = "thumbnail";
  return roles;
}
