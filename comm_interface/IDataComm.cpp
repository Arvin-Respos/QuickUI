#include "IDataComm.h"

bool IDataComm::init()
{
  return true;
}

int IDataComm::open()
{
  return 0;
}

void IDataComm::close()
{

}

bool IDataComm::hasReadData()
{
  return false;
}

qint64 IDataComm::readData(QByteArray &data,qint64 maxSize,int timeOut)
{
  Q_UNUSED(data)
  Q_UNUSED(maxSize)
  Q_UNUSED(timeOut)
  return 0;
}

qint64 IDataComm::writeData(QByteArray &data)
{
  Q_UNUSED(data)
  return 0;
}
