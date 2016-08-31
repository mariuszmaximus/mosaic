#include <QtGlobal>
#include <QtDebug>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("mosaic_cmd");
    QGuiApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("MoMosaic");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({"t", "The target picture.", "targetFileName"});
    parser.addOption({"s", "The mosaic tile pictures.", "sourceFileNames"});
    parser.process(app);

    QString targetFileName = parser.value("t");
    qInfo() << "Using target image: " << targetFileName;

    QString sourceFileNames = parser.value("s");
    qInfo() << "Using source files: " << sourceFileNames;

    return app.exec();
}
