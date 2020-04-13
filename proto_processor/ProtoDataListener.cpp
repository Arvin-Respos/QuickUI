#include "ProtoDataListener.h"
#include "CCommInterface.h"
#include "VendorProtoTypes.h"
#include "IDatagramComposer.h"

#ifdef PROTO_TYPE_GLINK_DL_MAP
#include "DatagramComposerGLinkMap.h"

#elif defined (PROTO_TYPE_BEIHAI_DL_MAP)
#include "DatagramComposerBeiHaiMap.h"

#elif defined (PROTO_TYPE_GLINK_TV)

#endif

const int DISCONNECT_TIMEOUT = 60 * 1000;

ProtoDataListener::ProtoDataListener(QObject *parent)
  :QThread (parent),m_strCommCfgFile(""),m_strCommAlias("")
{
  m_pCommInterface = nullptr;
  m_bFileFinishedFlag = false;
  m_bAliasFinishedFlag = false;
  m_bRunning = true;
}

ProtoDataListener::ProtoDataListener(QString strFileName,QString strAlias,QObject *parent)
  :QThread (parent),m_strCommCfgFile(strFileName),m_strCommAlias(strAlias)
{
  m_pCommInterface = nullptr;
  m_bFileFinishedFlag = true;
  m_bAliasFinishedFlag = true;
  m_bRunning = true;
}

ProtoDataListener::~ProtoDataListener()
{
  m_bRunning = false;
  delete m_pCommInterface;
  m_pCommInterface = nullptr;
  terminate ();
}

void ProtoDataListener::setCommCfgFileName(QString strFileName)
{
  m_strCommCfgFile = strFileName;
  m_bFileFinishedFlag = true;
}

void ProtoDataListener::setCommCfgAlias(QString strAlias)
{
  m_strCommAlias = strAlias;
  m_bAliasFinishedFlag = true;
}

QByteArray ProtoDataListener::dequeue()
{
    QMutexLocker locker(&m_QueueMutex);
    if(m_DataProtos.isEmpty ())
           return "";
    else
    {
        return m_DataProtos.dequeue ();
    }
}

void ProtoDataListener::enqueue(QByteArray &data)
{
  QMutexLocker locker(&m_QueueMutex);
  if(m_LastData != data)
  {
    m_DataProtos.enqueue (data);
    m_LastData = data;
  }
}

void ProtoDataListener::run()
{
    init();

    int nRet = m_pCommInterface->open ();
    if(nRet > 0)
    {
        printf("ProtoDataListener::run @ m_pCommInterface open failed!");
        return;
    }

    QTime tCommTime;
    tCommTime.start ();

    QByteArray readDataBuf;
    while(m_bRunning)
    {
       qint64 nReadCnt = m_pCommInterface->readData(readDataBuf);
      if(nReadCnt < 0)
      {
          if(tCommTime.elapsed () > DISCONNECT_TIMEOUT)
          {
              //TODO
          }
      }
      else
      {
          tCommTime.restart ();

          bool isFinished = false;
          QByteArray dataProto = packProtoData(readDataBuf,&isFinished);
          if (isFinished)
          {
              //TODO:根据数据的类型决定是否放入队列：如果是分段的报文则在未接收全部报文前不放入队列中，否则放入队列。
              enqueue(dataProto);
          }
      }
    }
}

void ProtoDataListener::init()
{
  if(!(m_bFileFinishedFlag && m_bAliasFinishedFlag))
  {
    printf("ProtoDataListener::init @ invalid configure file or alias!");
    return;
  }

  if(m_pCommInterface != nullptr)
  {
    delete m_pCommInterface;
    m_pCommInterface = nullptr;
  }
  m_pCommInterface = new CCommInterface(m_strCommCfgFile,m_strCommAlias);
}

/**
 * @brief ProtoDataListener::packProtoData      本函数的功能是根据项目的不同，把接收的协议数据
 *          做一些简单整理：如果是分段数据则缓存下来，直到接收到全部段再返回；否则，直接返回
 * @param data 接收的原始数据。
 * @param isFinished 如果是分段数据，在获取到全部段的数据后为true;如果是只有一条协议数据为true；
 *        其它情况为false;
 * @return 返回封装后的数据。
 */
QByteArray ProtoDataListener::packProtoData(QByteArray &data,bool *isFinished)
{
  #ifdef  PROTO_TYPE_GLINK_DL_MAP
  m_pDatagramComposer = new DatagramComposerGLinkMap(data);
  m_pDatagramComposer(data);
  #elif defined (PROTO_TYPE_BEIHAI_DL_MAP)

  #elif defined (PROTO_TYPE_GLINK_TV)

  #endif
}
