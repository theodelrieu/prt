#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <rangeloader.hpp>
#include <treeviewmodel.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto tree = new TreeViewModel;
    auto loader = new RangeLoader(tree);

    qmlRegisterUncreatableType<TreeViewModel>("RangeTreeModel", 1, 0, "TreeViewModel", "");
    qmlRegisterUncreatableType<RangeLoader>("RangeLoader", 1, 0, "RangeLoader", "");
    engine.rootContext()->setContextProperty("_rangeTreeModel", tree);
    engine.rootContext()->setContextProperty("_rangeLoader", loader);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
