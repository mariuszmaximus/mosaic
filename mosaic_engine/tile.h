#ifndef MOTILE_H
#define MOTILE_H

#include <QImage>


class MoTile {
public:
    MoTile();
    MoTile(const QImage& image);

    void setImage(const QImage& image);
    const QImage* getImage() const;
    QImage* getImage();
private:
    QImage image_;
};

#endif // MOTILE_H
