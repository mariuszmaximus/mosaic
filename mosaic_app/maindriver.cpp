#include <maindriver.h>
#include <QDir>
#include <QAbstractListModel>
#include <QString>
#include <QDebug>
#include <sourceimages.h>
#include <algorithm>

#include <tile.h>
#include <targetimage.h>


MoMainDriver::MoMainDriver(QObject *parent) :
    QObject(parent),
    sourceImages_(0) {
}

static MoTile loadTile(QString fn) {
    qDebug() << "loadTile(fn), fn == " << fn;
    QImage image(fn);
    MoTile tile(image);
    return tile;
}

void MoMainDriver::setSourceImages(QAbstractListModel *sourceImages) {
    sourceImages_ = sourceImages;
}

void MoMainDriver::start(QUrl targetUrl) {
    qDebug() << "targetUrl == " << targetUrl;
    QImage img(QDir::toNativeSeparators(targetUrl.toLocalFile()));
    MoTargetImage targetImage(img, img.size());

    std::vector<QString> inputFiles = getFileNames(sourceImages_);
    std::vector<MoTile> tiles;
    std::transform(inputFiles.cbegin(), inputFiles.cend(),
                   std::back_inserter(tiles),
                   loadTile);
    qDebug() << "tiles.size() == " << tiles.size();

    evolution_.constructInitialState(targetImage, tiles);
}

std::vector<QString> MoMainDriver::getFileNames(
        QAbstractListModel *inputImages) const {
    std::vector<QString> fileNames;
    fileNames.reserve(inputImages->rowCount());
    for (int i = 0; i < inputImages->rowCount(); ++i) {
        QUrl url = inputImages->data(inputImages->index(i),
                                     MoSourceImages::FileNameRole).toUrl();
        QString fn = url.toLocalFile();
        if (QFile(fn).exists()) {
            QString nativeFilename = QDir::toNativeSeparators(fn);
            fileNames.push_back(nativeFilename.toUtf8().constData());
        } else {
        }
    }
    return fileNames;
}
