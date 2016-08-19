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
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MoMosaicView>("MoMosaic", 1, 0, "MoMosaicView");

    // register some variables with QML engine.
    MoSourceImages sourceImages;
    engine.rootContext()->setContextProperty(
                "sourceImages", &sourceImages);
    MoImageProvider imageProvider(&sourceImages);
    engine.addImageProvider(QLatin1String("imageProvider"),
                            &imageProvider);
    MoMainDriver mainDriver;
    mainDriver.setSourceImages(&sourceImages);
    engine.rootContext()->setContextProperty(QLatin1String("mainDriver"),
                                             &mainDriver);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}
