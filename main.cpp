#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Macros.h"
#include "NumbersDB.h"
int main(int argc, char *argv[]) {
  qmlRegisterType<NumbersDB>(mcModule, 1, 0, "NumbersDB");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
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
