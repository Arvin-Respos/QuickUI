#ifndef SERIALPORTCOMM_H
#define SERIALPORTCOMM_H

#include "IDataComm.h"
#include  <QSerialPortInfo>
#include  <QSerialPort>

#ifndef Q_OS_WIN
#include <termios.h>
#include <unistd.h>
#endif

class SerialPortComm : public IDataComm
{
public:
    SerialPortComm();
    SerialPortComm(DataCommInfo &info);
    ~SerialPortComm();

    void setDataCommInfo(DataCommInfo &info){
      this->m_DataCommInfo = info;
      m_bParamFinished = true;
    }

private:
   #ifndef Q_OS_WIN
    void setTimeoutSize(struct termios *p,int timeout,int read_count);
    int setOpt(int timeout,int count);
    int initOpt(int baudrate, char parity,int data_bits,int stop_bits);
   #endif

  public:
    virtual bool init();
    virtual int open();
    virtual void close();
    virtual bool hasReadData();
    virtual qint64 readData(QByteArray &data,qint64 maxSize,int timeOut);
    virtual qint64 writeData(QByteArray &data);

private:
    bool m_bParamFinished;
    QSerialPort m_SerialPort;
 #ifndef Q_OS_WIN
    int m_nFd;
    int m_nBaudRate;
    int m_nDataBits;
    int m_nStopBits;
    char m_cParity;
 #endif
};

#endif // SERIALPORTCOMM_H
