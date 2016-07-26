#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QImage>
#include <QUrl>

class MoThumbnail
{
public:
    MoThumbnail();
    MoThumbnail(QImage i, QUrl u) : image(i), url(u) {}
    QImage getImage() const {return image;}
    QUrl getUrl() const { return url;}
    void load(QUrl u);
private:
    QImage image;
    QUrl url;
};

#endif // THUMBNAIL_H
