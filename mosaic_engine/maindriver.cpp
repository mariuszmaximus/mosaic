#include <maindriver.h>
#include <QDir>
#include <QAbstractListModel>
#include <QString>
#include <QDebug>
#include <QThread>
#include <sourceimages.h>
#include <algorithm>

#include <tile.h>
#include <targetimage.h>


struct MoMainDriver::EvolutionRunner : public QThread {
    EvolutionRunner(MoMosaicEvolution* evolution) : evolution_(evolution) {}
    virtual void run() {
        qDebug() << "in runner.run().";
        int i = 0;
        while (1) {
            qDebug() << "Taking step" << i;
            evolution_->takeStep();
            ++i;
        }
    }

    MoMosaicEvolution* evolution_;
};


MoMainDriver::MoMainDriver(QObject *parent) :
    QObject(parent),
    sourceImages_(0) {
}

MoMainDriver::~MoMainDriver() {}

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
    evolutionRunner_.reset(new EvolutionRunner(&evolution_));
    qDebug() << "before runner start";
    // For now we just leak this thread
    evolutionRunner_->start();
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
