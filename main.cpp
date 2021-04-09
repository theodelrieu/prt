#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <rangeloader.hpp>
#include <treeviewmodel.hpp>
#include <rangedisplayer.hpp>
#include <quizer.hpp>
#include <quizsettingsmodel.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto tree = new TreeViewModel;
    auto loader = new RangeLoader(tree);
    // TODO construct in quizer?
    auto quizSettings = new QuizSettingsModel;
    auto displayer = new RangeDisplayer(tree, quizSettings);
    auto quizer = new Quizer(displayer);


    qmlRegisterUncreatableType<TreeViewModel>("RangeTreeModel", 1, 0, "TreeViewModel", "");
    qmlRegisterUncreatableType<RangeLoader>("RangeLoader", 1, 0, "RangeLoader", "");
    qmlRegisterUncreatableType<RangeDisplayer>("RangeDisplayer", 1, 0, "RangeDisplayer", "");
    qmlRegisterUncreatableType<Quizer>("Quizer", 1, 0, "Quizer", "");
    qmlRegisterUncreatableType<QuizSettingsModel>("QuizSettingsModel", 1, 0, "QuizSettingsModel", "");
    engine.rootContext()->setContextProperty("_rangeTreeModel", tree);
    engine.rootContext()->setContextProperty("_rangeLoader", loader);
    engine.rootContext()->setContextProperty("_rangeDisplayer", displayer);
    engine.rootContext()->setContextProperty("_quizer", quizer);
    engine.rootContext()->setContextProperty("_quizSettings", quizSettings);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
