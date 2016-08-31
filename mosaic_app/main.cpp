#include <QtGlobal>
#include <QtDebug>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include <sourceimages.h>
#include <imageprovider.h>
#include <mosaicview.h>
#include <maindriver.h>


int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setApplicationName("mosaic_cmd");
    QGuiApplication::setApplicationVersion("0.0.1");
    QGuiApplication app(argc, argv);

    // Deal with command line arguments
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


    // Register types and create objects for QML code
    QQmlApplicationEngine engine;
    qmlRegisterType<MoMosaicView>("MoMosaic", 1, 0, "MoMosaicView");

    // register some variables with QML engine.
    MoSourceImages sourceImages;
    engine.rootContext()->setContextProperty(
                "sourceImages", &sourceImages);
    MoImageProvider* imageProvider = new MoImageProvider(&sourceImages);
    engine.addImageProvider(QLatin1String("imageProvider"),
                            imageProvider);
    MoMainDriver mainDriver;
    mainDriver.setSourceImages(&sourceImages);
    engine.rootContext()->setContextProperty(QLatin1String("mainDriver"),
                                             &mainDriver);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    QObject* mosaicView =
            engine.rootObjects().value(0)->findChild<QObject*>(QString("mosaicView"));
    if (mosaicView) {
        QObject::connect(&mainDriver, &MoMainDriver::modelChanged,
                         static_cast<MoMosaicView*>(mosaicView),
                         &MoMosaicView::setModel);
    } else {
        qDebug() << "mosaicView not found.";
    }

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}
