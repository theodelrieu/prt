#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtPlugin>
#include <quizer.hpp>
#include <quizsettinggroupmodel.hpp>
#include <rangedisplayer.hpp>
#include <rangeloader.hpp>
#include <treeviewmodel.hpp>

Q_IMPORT_PLUGIN(QtQuick2Plugin);
Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin);
Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin);
Q_IMPORT_PLUGIN(QtQuickControls2Plugin);
Q_IMPORT_PLUGIN(QtQuickControls2FusionStylePlugin);
Q_IMPORT_PLUGIN(QtQuickControls2FusionStyleImplPlugin);
Q_IMPORT_PLUGIN(QtQuickControls2BasicStylePlugin);
Q_IMPORT_PLUGIN(QtQuickControls2NativeStylePlugin);
Q_IMPORT_PLUGIN(QtQuickControls2WindowsStylePlugin);
Q_IMPORT_PLUGIN(QtQuickControls2ImplPlugin);
Q_IMPORT_PLUGIN(QtQuick_WindowPlugin);
Q_IMPORT_PLUGIN(QtQmlPlugin);
Q_IMPORT_PLUGIN(QtLabsPlatformPlugin);
Q_IMPORT_PLUGIN(QtQmlModelsPlugin);
Q_IMPORT_PLUGIN(QtQmlWorkerScriptPlugin);

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  auto tree = new TreeViewModel;
  auto loader = new RangeLoader(tree);
  // TODO construct in quizer?
  auto quizSettings = new QuizSettingGroupModel;
  auto displayer = new RangeDisplayer(tree, quizSettings);
  auto quizer = new Quizer(displayer);

  qmlRegisterUncreatableType<TreeViewModel>("RangeTreeModel", 1, 0,
                                            "TreeViewModel", "");
  qmlRegisterUncreatableType<RangeLoader>("RangeLoader", 1, 0, "RangeLoader",
                                          "");
  qmlRegisterUncreatableType<RangeDisplayer>("RangeDisplayer", 1, 0,
                                             "RangeDisplayer", "");
  qmlRegisterUncreatableType<Quizer>("Quizer", 1, 0, "Quizer", "");
  qmlRegisterUncreatableType<QuizSettingGroupModel>(
      "QuizSettingGroupModel", 1, 0, "QuizSettingGroupModel", "");
  engine.rootContext()->setContextProperty("_rangeTreeModel", tree);
  engine.rootContext()->setContextProperty("_rangeLoader", loader);
  engine.rootContext()->setContextProperty("_rangeDisplayer", displayer);
  engine.rootContext()->setContextProperty("_quizer", quizer);
  engine.rootContext()->setContextProperty("_quizSettings", quizSettings);
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
