#ifndef PROTODATALISTENER_H
#define PROTODATALISTENER_H

#include <QtCore/QObject>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QByteArray>
#include <QTime>

class CCommInterface;
class IDatagramComposer;

class ProtoDataListener:public QThread
{
  Q_OBJECT
public:
  explicit ProtoDataListener(QObject *parent = nullptr);
  ProtoDataListener(QString strFileName,QString strAlias,QObject *parent = nullptr);
  ~ProtoDataListener();

public:
  void setCommCfgFileName(QString strFileName);
  void setCommCfgAlias(QString strAlias);

public:
  QByteArray dequeue();
   void enqueue(QByteArray &data);

protected:
  virtual void run();

private:
   void init();
   QByteArray packProtoData(QByteArray &data,bool *isFinished);

private:
   bool m_bFileFinishedFlag;
   bool m_bAliasFinishedFlag;
   bool m_bRunning;

private:
  QString m_strCommCfgFile;
  QString m_strCommAlias;
  QMutex m_QueueMutex;
  QQueue <QByteArray> m_DataProtos;
  QByteArray m_LastData;

  CCommInterface *m_pCommInterface;
  IDatagramComposer *m_pDatagramComposer;
};

#endif // PROTODATALISTENER_H
