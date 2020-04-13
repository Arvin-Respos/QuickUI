#include "CANSocketComm.h"

#ifndef Q_OS_WIN
#include <sys/types.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#endif

CANSocketComm::CANSocketComm()
    :IDataComm(),m_bParamFinished(false)
{
 #ifndef Q_OS_WIN
  m_nFd = -1;
#endif
}

CANSocketComm::CANSocketComm(DataCommInfo &info)
  :IDataComm (info),m_bParamFinished(true)
{
 #ifndef Q_OS_WIN
  m_nFd = -1;
#endif
}

CANSocketComm::~CANSocketComm()
{

}

 bool CANSocketComm::init()
 {
#ifndef Q_OS_WIN
    m_nFd = -1;
#endif
    if(!m_bParamFinished)
    {
        qDebug("CANSocketComm::init @ invalid CAN parameter!");
        return false;
    }
    return true;
 }

int CANSocketComm::open()
{
  bool bRet = init();
  if(!bRet)
  {
      return (-1);
  }

#ifndef Q_OS_WIN
  struct sockaddr_can addr;
  struct ifreq ifr;

  if ((m_nFd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
  {
     qDebug("CANSocketComm::open @ create socket failed!");
     return (-1);
  }

  //set up can interface
  strcpy(ifr.ifr_name, m_DataCommInfo.devName ().toStdString ().c_str ());

  //assign can device
  ioctl(m_nFd, SIOCGIFINDEX, &ifr);
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  //bind can device
  if(bind(m_nFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
     qDebug("CANSocketComm::open @ bind can device failed!");
      ::close(m_nFd);
      return (-2);
  }
  return m_nFd;
#else
  qDebug("the interface is not supported!");
  return 0;
#endif
}

void CANSocketComm::close()
{
#ifndef Q_OS_WIN
    ::close(m_nFd);
#else

#endif
}

bool CANSocketComm::hasReadData()
{
  return  true;
}

qint64 CANSocketComm::readData(QByteArray &data,qint64 maxSize,int timeOut)
{
    Q_UNUSED(maxSize)
    Q_UNUSED(timeOut)

 #ifndef Q_OS_WIN
    int nLen = 0;
    struct can_frame frame;
    memset(&frame,0,sizeof( struct can_frame));
    nLen = read(m_nFd, &frame, sizeof(struct can_frame));

    quint32 unCanId = frame.can_id;
    data.append (static_cast<char>((unCanId & 0x1FE00000) >> 21));
    data.append (static_cast<char>((unCanId & 0x1FE000) >> 13));
    data.append (static_cast<char>((unCanId & 0x1000) >> 12));
    data.append (static_cast<char>((unCanId & 0xF00) >> 8));
    data.append (static_cast<char>(unCanId & 0xFF));
    data.append (static_cast<char>(0x00));
    data.append (static_cast<char>(frame.can_dlc));
    for(int i=0;i < frame.can_dlc; i++)
   {
        data.append (static_cast<char>(frame.data[i]));
    }
    return frame.can_dlc;
 #else
  Q_UNUSED(data)
  qDebug("the interface is not supported!");
  return 0;
 #endif
}

qint64 CANSocketComm::writeData(QByteArray &data)
{
 #ifndef Q_OS_WIN
  int nLen = 0;
  struct can_frame frame;

  quint32 canId = 0;
  quint8 tempCanId = static_cast<quint8>(data[0]);
  canId += static_cast<quint32>(tempCanId << 21);

  tempCanId = static_cast<quint8>(data[1]);
  canId += static_cast<quint32>(tempCanId << 13);

  tempCanId = static_cast<quint8>(data[2]);
  canId += static_cast<quint32>(tempCanId << 12);

  tempCanId = static_cast<quint8>(data[3]);
  canId += static_cast<quint32>(tempCanId << 8);

  tempCanId = static_cast<quint8>(data[4]);
  canId += static_cast<quint32>(tempCanId);

  //external frame
  canId +=static_cast<quint32>(1<< 31);

  memset(&frame,0,sizeof( struct can_frame));
  frame.can_dlc = data[6];
  frame.can_id = canId;
  for(int i = 0; i < frame.can_dlc; i++)
 {
      frame.data[i] = data.at(7+i);
 }
  nLen = write(m_nFd, &frame, sizeof(struct can_frame));

  return nLen;
#else
  Q_UNUSED(data)
  qDebug("the interface is not supported!");
  return 0;
#endif
}
