#ifndef UDPSOCKETCOMM_H
#define UDPSOCKETCOMM_H

#include <QHostAddress>
#include <QUdpSocket>
#include "IDataComm.h"

/**
 * @brief The UDPSocketComm class
 */

class UDPSocketComm : public IDataComm
{
public:
  UDPSocketComm();
  UDPSocketComm(DataCommInfo &info);
  ~UDPSocketComm();

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
  QHostAddress m_SourceAddr;
  quint16 m_nSrcPort;
  QHostAddress m_TargetAddr;
  quint16 m_nTargetPort;
  QUdpSocket *m_pUdpSocket;
};

#endif // UDPSOCKETCOMM_H
