#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include <sourceimages.h>
#include <imageprovider.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    MoSourceImages sourceImages;
    engine.rootContext()->setContextProperty(
                "sourceImages", &sourceImages);
    MoImageProvider* imageProvider = new MoImageProvider(&sourceImages);
    engine.addImageProvider(QLatin1String("imageProvider"),
                            imageProvider);

    QString qmlPath = "qrc:/main.qml";
    engine.load(QDir::toNativeSeparators(qmlPath));

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}
