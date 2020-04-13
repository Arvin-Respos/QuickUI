#include <QtCore/QCoreApplication>
#include <QString>
#include "DataCommAdapter.h"


#define  CFG_FILE_COMM   ("datacom.cfg")

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  DataCommAdapter adapter(QString(CFG_FILE_COMM),QString("udp"));
  adapter.open();

  return a.exec();
}
