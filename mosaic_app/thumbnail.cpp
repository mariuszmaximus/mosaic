#include "thumbnail.h"

MoThumbnail::MoThumbnail()
{
}

void MoThumbnail::load(QUrl u)
{
    image = QImage(u.toLocalFile());
    url = u;
}
