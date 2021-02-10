#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <rangeloader.hpp>
#include <treemodeladaptor.h>
#include <treemodel.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto tree = new TreeModel;
    auto loader = new RangeLoader(tree);

    qmlRegisterUncreatableType<TreeModel>("RangeTreeModel", 1, 0, "TreeModel", "");
    qmlRegisterUncreatableType<RangeLoader>("RangeLoader", 1, 0, "RangeLoader", "");
    qmlRegisterType<TreeModelAdaptor>("TreeModelAdaptor", 1, 0, "TreeModelAdaptor");
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
