#ifndef CANSOCKETCOMM_H
#define CANSOCKETCOMM_H

#include "IDataComm.h"

class CANSocketComm:public IDataComm
{
public:
    CANSocketComm();
    CANSocketComm(DataCommInfo &info);
    ~CANSocketComm();

    void setDataCommInfo(DataCommInfo &info){
      this->m_DataCommInfo = info;
      m_bParamFinished = true;
    }

  public:
    virtual bool init();
    virtual int open();
    virtual void close();
    virtual bool hasReadData();
    virtual qint64 readData(QByteArray &data,qint64 maxSize,int timeOut);
    virtual qint64 writeData(QByteArray &data);

private:
  bool m_bParamFinished;
 #ifndef Q_OS_WIN
  int m_nFd; //CAN设备的文件描述符
  #endif
};

#endif // CANSOCKETCOMM_H
