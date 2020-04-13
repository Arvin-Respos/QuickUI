#include <QtCore/QCoreApplication>

#include "assetmanager.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

//  qputenv ("RESFILE_DIR","/home/ui/res/");

   AssetManager manager = AssetManager::getInstance ();
   QVariant var = manager.getResource ("text-array@hello",2);
   qDebug("var:%s",var.toString ().toStdString ().c_str ());

  return a.exec();
}
