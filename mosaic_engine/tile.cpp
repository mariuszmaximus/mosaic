#include "tile.h"

MoTile::MoTile() {
}

MoTile::MoTile(const QImage& image) : image_(image) {
}

void MoTile::setImage(const QImage &image) {
    image_ = image;
}

QImage* MoTile::getImage() {
    return &image_;
}

const QImage* MoTile::getImage() const {
    return &image_;
}
