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
    parser.addPositionalArgument("sources",
                                 "The mosaic tile pictures.");
    parser.process(app);

    QString targetFileName = parser.value("t");
    qInfo() << "Using target image: " << targetFileName;

    QStringList sourceFileNames = parser.positionalArguments();
    qInfo() << "Using source files: " << sourceFileNames;

    return app.exec();
}
