#include <maindriver.h>
#include <QDir>
#include <QAbstractListModel>
#include <QString>
#include <QThread>
#include <QDebug>
#include <algorithm>

#include <tile.h>
#include <targetimage.h>
#include <sourceimages.h>
#include <mosaicmodel.h>
#include <evolutionrunner.h>
#include <mosaicupdatedelay.h>
#include <mosaicupdateoptimize.h>
#include <badness.h>
#include <badnesscomposite.h>


MoMainDriver::MoMainDriver(QObject *parent) :
    QObject(parent),
    sourceImages_(0) {
}

MoMainDriver::~MoMainDriver() {
    shutDownEvolutionRunner();
}

static MoTile loadTile(QString fn) {
    QImage image(fn);
    MoTile tile(image);
    return tile;
}

void MoMainDriver::setSourceImages(QAbstractListModel *sourceImages) {
    sourceImages_ = sourceImages;
}

void MoMainDriver::start() {
    QImage img(QDir::toNativeSeparators(targetUrl_.toLocalFile()));
    MoTargetImage targetImage(img, img.size());

    std::vector<QString> inputFiles = getFileNames(sourceImages_);
    std::vector<MoTile> tiles;
    std::transform(inputFiles.cbegin(), inputFiles.cend(),
                   std::back_inserter(tiles),
                   loadTile);

    evolution_.constructInitialState(targetImage, tiles);

    evolution_.addUpdate(
                std::unique_ptr<MoMosaicUpdate>(new MoMosaicUpdateDelay));

    std::unique_ptr<MoBadness> badness{new MoBadnessComposite};
    std::unique_ptr<MoMosaicUpdateOptimize> updateOptimize{
            new MoMosaicUpdateOptimize};
    updateOptimize->setBadness(std::move(badness));
    evolution_.addUpdate(std::move(updateOptimize));


    if (evolutionRunner_) {
        evolutionRunner_->terminate();
    }
    evolutionRunner_.reset(new MoEvolutionRunner);
    evolutionRunner_->setEvolution(&evolution_);
    connect(evolutionRunner_.get(), &MoEvolutionRunner::modelChanged,
            this, &MoMainDriver::setCurrentModel);
    evolutionRunner_->start();
}

void MoMainDriver::shutDownEvolutionRunner()
{
    if (evolutionRunner_) {
        evolutionRunner_->stop();
        if (!evolutionRunner_->wait(100)) {
            evolutionRunner_->terminate();
        }
        evolutionRunner_.reset(nullptr);
    }
}

void MoMainDriver::stop() {
    shutDownEvolutionRunner();
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

std::shared_ptr<MoMosaicModel> MoMainDriver::getCurrentModel() {
    return currentModel_;
}

void MoMainDriver::setCurrentModel(std::shared_ptr<MoMosaicModel> newModel) {
    currentModel_ = newModel;
    emit modelChanged(newModel);
}

void MoMainDriver::setTargetUrl(QUrl targetUrl) {
    targetUrl_ = targetUrl;
    emit targetUrlChanged(targetUrl_);
}

QUrl MoMainDriver::getTargetUrl() {
    return targetUrl_;
}
