#include "SerialPortComm.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

SerialPortComm::SerialPortComm()
    :IDataComm(),m_bParamFinished(false)
{
#if QT_VERSION >= 0x050100

#else

#endif
}

SerialPortComm::SerialPortComm(DataCommInfo &info)
    :IDataComm(info),m_bParamFinished(true)
{
#if QT_VERSION >= 0x050100
    init();
#else

#endif
}

SerialPortComm::~SerialPortComm()
{
#if QT_VERSION >= 0x050100

#else

#endif
}

#ifndef Q_OS_WIN
void SerialPortComm::setTimeoutSize(struct termios *p,int nTimeOut,int nReadCount)
{
  p->c_cc[VTIME] = nTimeOut;
  p->c_cc[VMIN] = nReadCount;
}

int SerialPortComm::setOpt(int timeout,int count)
{
  int ret = 0;
  struct termios options;
  memset(&options, 0, sizeof(options)) ;
  ret = tcgetattr(m_nFd, &options); //获取原有的串口属性的配置
  if(ret != 0)
  {
      qDebug("SerialPortComm::setOpt @ tcgetattr() failed:%s",strerror(errno)) ;
      return (-1);
  }

  if((options.c_cc[VTIME] == timeout) && (options.c_cc[VMIN] == count))
  {
      return 0;
  }

  setTimeoutSize(&options,timeout,count);
  if(tcsetattr(m_nFd, TCSANOW, &options) != 0)
  {
      qDebug("SerialPortComm::setOpt @ tcsetattr() failed:%s",strerror(errno)) ;
      return (-2);
  }
  return 0;
}

int SerialPortComm::initOpt(int baudrate, char parity,int data_bits,int stop_bits)
{
  int ret = 0;
  struct termios options;

  if(m_nFd == -1)
  {
      qDebug("SerialPortComm::initOpt @ invalid fd!") ;
      return (-1);
  }

  memset(&options, 0, sizeof(options)) ;
  ret = tcgetattr(m_nFd, &options); //获取原有的串口属性的配置
  if(ret != 0)
  {
      qDebug("SerialPortComm::initOpt @ tcgetattr() failed:%s\n",strerror(errno)) ;
      return (-2);
  }

  //串口准备
  options.c_cflag|=(CLOCAL|CREAD ); // CREAD 开启串行数据接收，CLOCAL并打开本地连接模式
  options.c_cflag &=~CSIZE;// 先使用CSIZE做位屏蔽

  //设置波特率。输入输出波特率设置为一致
  cfsetispeed(&options, baudrate);
  cfsetospeed(&options,baudrate);

  //设置校验方式
  switch(parity)
  {
      case 'N': //无校验
      {
          options.c_cflag &= ~PARENB;
      }
      break;

      case 'O': //奇校验
      {
          options.c_cflag |= PARENB;
          options.c_cflag |= PARODD;
          options.c_iflag |= (INPCK | ISTRIP);
      }
      break;

      case 'E': //偶校验
      {
          options.c_iflag |= (INPCK | ISTRIP);
          options.c_cflag |= PARENB;
          options.c_cflag &= ~PARODD;
      }
      break;

      case 'S':
      {
          options.c_cflag &= ~PARENB;        //清除校验位
          options.c_cflag &= ~CSTOPB;        //??????????????
          options.c_iflag |= INPCK;            //disable pairty checking
      }
      break;
  }

  //设置数据位
  options.c_cflag |= CLOCAL | CREAD;
  options.c_cflag &= ~CSIZE;
  switch(data_bits)        //设置数据位数
  {
  case 7:
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS7;
      break;

  case 8:
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;
      break;

  default:
      qDebug("SerialPortComm::initOpt @ Unsupported data size.\n");
      return (-3);
  }

  //设置停止位
  switch(stop_bits)
  {
      case 1:
      options.c_cflag &= ~CSTOPB;
      break;

      case 2:
      options.c_cflag |= CSTOPB;
      break;

      default:
      qDebug("SerialPortComm::initOpt @ Unsupported stopbits.\n");
      return (-4);
  }

  //其它设置
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag &= ~OPOST;
  options.c_oflag &= ~(ONLCR | OCRNL);    //添加的
  options.c_iflag &= ~(ICRNL | INLCR);
  options.c_iflag &= ~(IXON | IXOFF | IXANY);    //添加的

  tcflush(m_nFd, TCIFLUSH);

  setTimeoutSize(&options,0,0);

  //Update the Opt and do it now
  if(tcsetattr(m_nFd, TCSANOW, &options) != 0)
  {
      qDebug("SerialPortComm::initOpt @  tcsetattr failed!\n");
      return (-5);
  }

  return 0;
}
#endif

bool SerialPortComm::init()
{
    //设备名称即是串口设备名，参数即是[波特率],[校验方式],[数据位],[停止位]
    QStringList lstParam = this->m_DataCommInfo.parameter().split(",");
    if(lstParam.size() != 4)
    {
        qDebug("SerialPortComm::init @ serial port parameter is invalid!");
        return false;
    }

    QString strBaudRate = lstParam.at(0);
    QString strParity = lstParam.at(1);
    QString strDataBits = lstParam.at(2);
    QString strStopBits = lstParam.at(3);

#if QT_VERSION >= 0x050100
   #ifdef Q_OS_WIN
    //波特率
    bool bOk;
    quint32 nBaudRate = strBaudRate.toUInt(&bOk,10);
    if(!bOk)
    {
        qDebug("SerialPortComm::init @ serial port baudrate is invalid!");
        return false;
    }
    m_SerialPort.setBaudRate(static_cast<enum QSerialPort::BaudRate>(nBaudRate));

    //校验方式
    if(strParity == "NONE")
    {
        m_SerialPort.setParity(QSerialPort::NoParity);
    }
    else if(strParity == "EVEN")
    {
        m_SerialPort.setParity(QSerialPort::EvenParity);
    }
    else if(strParity == "ODD")
    {
        m_SerialPort.setParity(QSerialPort::OddParity);
    }
    else if(strParity == "SPACE")
    {
        m_SerialPort.setParity(QSerialPort::SpaceParity);
    }
    else if(strParity == "MARK")
    {
        m_SerialPort.setParity(QSerialPort::MarkParity);
    }
    else
    {
        qDebug("SerialPortComm::init @ the parity is not supported!");
        return false;
    }

    //数据位
    quint32 nDataBits = strDataBits.toUInt(&bOk,10);
    if(!bOk)
    {
        qDebug("SerialPortComm::init @ data bits is invalid!");
        return false;
    }
    m_SerialPort.setDataBits(static_cast<enum QSerialPort::DataBits>(nDataBits));

    //停止位
    quint32 nStopBits = strStopBits.toUInt(&bOk,10);
    if(!bOk)
    {
        qDebug("SerialPortComm::init @ data bits is invalid!");
        return false;
    }
    m_SerialPort.setStopBits(static_cast<enum QSerialPort::StopBits>(nStopBits));

    //设备名
    m_SerialPort.setPortName(m_DataCommInfo.devName());

    m_SerialPort.setFlowControl(QSerialPort::NoFlowControl);
   #else
    //TODO:使用linux接口操作串口
      bool bOk;
      m_nBaudRate = strBaudRate.toInt(&bOk,10);
      if(!bOk)
      {
          qDebug("SerialPortComm::init @ invalid baudrate!");
          return false;
      }
      m_cParity = strParity.at(0).toLatin1();
      m_nDataBits = strDataBits.toInt(&bOk,10);
      if(!bOk)
      {
          qDebug("SerialPortComm::init @ invalid databits!");
          return false;
      }
      m_nStopBits = strStopBits.toInt(&bOk,10);
      if(!bOk)
      {
          qDebug("SerialPortComm::init @ invalid stop bits!");
          return false;
      }
  #endif
#else
    qDebug("this QT version is not supported!");
#endif

    return true;
}

int SerialPortComm::open()
{
#if QT_VERSION >= 0x050100
   #ifdef Q_OS_WIN
    if(m_SerialPort.isOpen())
    {
        m_SerialPort.close();
    }
    bool ret = m_SerialPort.open(QIODevice::ReadWrite);
    if(!ret)
    {
        qDebug("SerialPortComm::open @ serial port open failed!");
        return (-1);
    }
    #else
  m_nFd = ::open(this->m_DataCommInfo.devName().toStdString ().c_str (),O_RDWR|O_NOCTTY|O_NDELAY) ; //打开串口设备
  if(m_nFd < 0)
  {
      printf("open tty failed:%s\n", strerror(errno));
      m_nFd = -1;
      return (-1);
  }

  if(initOpt(m_nBaudRate,m_cParity,8,1))
  {
      m_nFd = -1;
      return (-2);
  }

  return m_nFd;
    #endif
#else
    qDebug("this QT version is not supported!");
#endif

    return (1);
}

void SerialPortComm::close()
{
#if QT_VERSION >= 0x050100
   #ifdef Q_OS_WIN
       m_SerialPort.close();
   #else
    ::close(m_nFd);
    #endif
#else
    qDebug("this QT version is not supported!");
#endif
}

bool SerialPortComm::hasReadData()
{
#if QT_VERSION >= 0x050100
    #ifdef Q_OS_WIN
        return (m_SerialPort.waitForReadyRead());
    #else

     #endif
#else
    qDebug("this QT version is not supported!");
#endif
}

qint64 SerialPortComm::readData(QByteArray &data,qint64 maxSize,int timeOut)
{
#if QT_VERSION >= 0x050100
    #ifdef Q_OS_WIN
        Q_UNUSED(timeOut)

      data = m_SerialPort.readAll();
    #else
      int readCnt = 0;
      if(setOpt(timeOut/100,maxSize))
      {
          printf("read_com :: set_opt failed\n");
          return (-1);
      }
      char buf[1024] = {0};

     readCnt =  read(m_nFd,buf,maxSize);
     data.resize (readCnt);
     data.append (buf,readCnt);
     #endif
#else
    Q_UNUSED(timeOut)
    Q_UNUSED(maxSize)
    qDebug("this QT version is not supported!");
#endif

    return static_cast<int>(data.size());
}

qint64 SerialPortComm::writeData(QByteArray &data)
{
#if QT_VERSION >= 0x050100
    #ifdef Q_OS_WIN
        return (m_SerialPort.write(data.data(),data.size()));
    #else
    int nCount = 0;
    nCount = write(m_nFd,data.data(),data.size());
    return nCount;
     #endif
#else
    qDebug("this QT version is not supported!");
#endif
}
