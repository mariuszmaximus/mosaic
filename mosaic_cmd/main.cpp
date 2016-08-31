#include <QCommandLineParser>
#include <QCommandLineOption>


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("MoMosaic");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({"t", "The target picture.", "target_picture"});
    parser.addOption({"s", "The mosaic tile pictures.", "source_pictures"});
    parser.process(app);

    return app.exec();
}
