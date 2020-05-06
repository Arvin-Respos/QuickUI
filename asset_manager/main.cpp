#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlEngine>
#include "assetmanager.h"

int main(int argc, char *argv[])
{
//  qputenv ("RESFILE_DIR","/home/ui/res/");
  qmlRegisterSingletonType<AssetManager>("QuickUi.Sources",1,0,"AssetManager",assetmanager_provider);

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
