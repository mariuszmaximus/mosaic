#include <maindriver.h>
#include <QDir>
#include <sourceimages.h>
#include <QDebug>


MoMainDriver::MoMainDriver(QObject *parent) :
    QObject(parent) {
}

void MoMainDriver::start(QAbstractListModel* inputImages, QUrl targetUrl) {
    Q_UNUSED(inputImages);
    Q_UNUSED(targetUrl);
}

std::vector<std::string> MoMainDriver::getFileNames(
        QAbstractListModel *inputImages) const {
    std::vector<std::string> fileNames;
    fileNames.reserve(inputImages->rowCount());
    for (int i = 0; i < inputImages->rowCount(); ++i) {
        QUrl url = inputImages->data(inputImages->index(i),
                                     MoSourceImages::FileNameRole).toUrl();
        QString fn = url.toLocalFile();
        if (QFile(fn).exists()) {
            QString nativeFilename = QDir::toNativeSeparators(fn);
            fileNames.push_back(std::string(nativeFilename.toUtf8().constData()));
        } else {
        }
    }
    return fileNames;
}

void MoMainDriver::setTargetImage(const QUrl& newTarget) {
    Q_UNUSED(newTarget);
    qDebug() << "setTargetImage";
}

void MoMainDriver::targetImageChanged() {
    qDebug() << "targetImageChanged";
}
