#include "UDPSocketComm.h"

UDPSocketComm::UDPSocketComm()
  :IDataComm(),m_bParamFinished(false)
{

}

UDPSocketComm::UDPSocketComm(DataCommInfo &info)
  :IDataComm (info),m_bParamFinished(true)
{

}

UDPSocketComm::~UDPSocketComm()
{
    delete m_pUdpSocket;
    m_pUdpSocket = nullptr;
}

bool UDPSocketComm::init()
{
  if(!m_bParamFinished)
  {
    qDebug("UDPSocketComm::init @ the param is not finished!");
    return false;
  }

  //解析参数结构如下:
  //[接收IP地址],[接收端口],[发送IP地址],[发送端口]
  QStringList lstParam = m_DataCommInfo.parameter().split(":");
  int nSize = lstParam.size();
  if(nSize != 4)
  {
    qDebug("UDPSocketComm::init @ the param is invalid!");
    return false;
  }

  //源地址
  QString strSrcAddr = lstParam.at(0);
  if( strSrcAddr == "localhost")
  {
        m_SourceAddr.setAddress(QHostAddress::LocalHost);
  }
  else if(strSrcAddr == "any")
  {
    m_SourceAddr.setAddress(QHostAddress::AnyIPv4);
  }
  else if(strSrcAddr == "broadcast")
  {
    m_SourceAddr.setAddress(QHostAddress::Broadcast);
  }
  else
  {
     QStringList srcIP = strSrcAddr.split(".");
     if(srcIP.size() != 4)
     {
        qDebug("UDPSocketComm::init @ the source ip is invalid!");
        return false;
     }
     else
     {
           m_SourceAddr.setAddress(strSrcAddr);
     }
  }

  //源端口
  QString strSrcPort = lstParam.at(1);
  int ret = strSrcPort.indexOf(QRegExp("\\D"), 0);
  if(ret != -1)
  {
      qDebug("UDPSocketComm::init @ the source port is invalid!");
      return false;
  }
  m_nSrcPort = static_cast<quint16>(strSrcPort.toUInt(nullptr,10));

  //目标地址
  QString strTargetAddr = lstParam.at(2);
  if( strTargetAddr == "localhost")
  {
        m_TargetAddr.setAddress(QHostAddress::LocalHost);
  }
  else if(strTargetAddr == "any")
  {
    m_TargetAddr.setAddress(QHostAddress::AnyIPv4);
  }
  else if(strTargetAddr == "broadcast")
  {
    m_TargetAddr.setAddress(QHostAddress::Broadcast);
  }
  else
  {
     QStringList targetIP = strTargetAddr.split(".");
     if(targetIP.size() != 4)
     {
        qDebug("UDPSocketComm::init @ the target ip is invalid!");
        return false;
     }
     else
     {
           m_TargetAddr.setAddress(strTargetAddr);
     }
  }

  //目标端口
  QString strTargetPort = lstParam.at(3);
  ret = strTargetPort.indexOf(QRegExp("\\D"), 0);
  if(ret != -1)
  {
      qDebug("UDPSocketComm::init @ the target port is invalid!");
      return false;
  }
  m_nTargetPort = static_cast<quint16>(strTargetPort.toUInt(nullptr,10));

   return true;
}

int UDPSocketComm::open()
{
    if(m_pUdpSocket->isOpen())
    {
        m_pUdpSocket->close();
        delete m_pUdpSocket;
        m_pUdpSocket = nullptr;
    }

    m_pUdpSocket  = new QUdpSocket(this);
    if(m_pUdpSocket  == nullptr)
    {
        qDebug("UDPSocketComm::open @ open udp socket failed!");
        return (-1);
    }
    bool bBindOk = m_pUdpSocket->bind(this->m_SourceAddr,this->m_nSrcPort,QAbstractSocket::ShareAddress);
    if(!bBindOk)
    {
        qDebug("UDPSocketComm::open @ bind udp socket failed!");
        return (-1);
    }
    return (1);
}

void UDPSocketComm::close()
{
    m_pUdpSocket->close();
}

bool UDPSocketComm::hasReadData()
{
    return (m_pUdpSocket->hasPendingDatagrams());
}

qint64 UDPSocketComm::readData(QByteArray &data,qint64 maxSize,int timeOut)
{
    Q_UNUSED(maxSize)
    Q_UNUSED(timeOut)

    qint64 readSize = m_pUdpSocket->pendingDatagramSize();
    if(readSize == 0)
    {
        return (0);
    }
    return (m_pUdpSocket->readDatagram(data.data(),readSize));
}

qint64 UDPSocketComm::writeData(QByteArray &data)
{
    if(data.size() == 0)
    {
        return 0;
    }
    return (m_pUdpSocket->writeDatagram(data.data(),data.size(),m_TargetAddr,m_nTargetPort));
}
