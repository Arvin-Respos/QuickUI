#include <QtCore/QCoreApplication>
#include <QString>
#include "CCommInterface.h"
#include <cstdio>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  CCommInterface commPort(QString("comm_host.txt"),QString("canio"));
  if(commPort.open () < 0)
  {
      exit(-1);
  }

  QByteArray data;
  qint64 nReadCount = 0;
  while(true)
  {
      if(commPort.hasReadData ())
      {
          nReadCount = commPort.readData (data,1024,1000);
          if(nReadCount > 0)
          {
                for(int i = 0; i < nReadCount; i++)
              {
                 printf("%02x ",data.at (i));
              }
              printf("\n");
              commPort.writeData (data);
           }
       }
  }

  return a.exec();
}
