#ifndef IDATACOMM_H
#define IDATACOMM_H

#include <QString>
#include <QObject>
#include "DataCommProtoType.h"

/**
 * @brief The IDataComm class
 */

class IDataComm:public QObject
{
    Q_OBJECT
public:
  explicit IDataComm(void){}
  IDataComm(DataCommInfo &info) {
    m_DataCommInfo = info;
  }
  virtual ~IDataComm(){}

public:
  void setDataCommInfo(DataCommInfo &info) {
    m_DataCommInfo = info;
  }

public:
  virtual bool init();
  virtual int open();
  virtual void close();
  virtual bool hasReadData();
  virtual qint64 readData(QByteArray &data,qint64 maxSize,int timeOut);
  virtual qint64 writeData(QByteArray &data);

public:
  DataCommInfo m_DataCommInfo;
};


#endif // IDATACOMM_H
