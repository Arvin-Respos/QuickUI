#include "CCommInterface.h"

#include "ConfigParse.h"
#include  "include.h"

CCommInterface::CCommInterface()
    :m_bFileOk(false),m_bAliasOk(false)
{
    m_strFileName = "";
    m_strAlias = "";
    m_pConfigParser = nullptr;
}

CCommInterface::CCommInterface(QString file,QString alias)
{
    m_strFileName = file;
    m_strAlias = alias;
    m_bFileOk = true;
    m_bAliasOk = true;
    m_pConfigParser = nullptr;
    init();
}

CCommInterface::~CCommInterface()
{
    if(!m_pConfigParser)
    {
        delete  m_pConfigParser;
        m_pConfigParser = nullptr;
    }

    if(!m_pDataComm)
    {
        delete m_pDataComm;
        m_pDataComm = nullptr;
    }
}

bool CCommInterface::init()
{
    m_pConfigParser = new ConfigParse(m_strFileName,m_strAlias);
    if(m_pConfigParser == nullptr)
    {
        qDebug("DataCommAdapter::init @ alloc m_pConfigParser failed!");
        return false;
    }

    bool bOk;
    DataCommInfo info =  m_pConfigParser->getCommInfo(&bOk);
    if(bOk)
    {
        qDebug("DataCommAdapter::init @ getCommInfo failed!");
        return false;
    }

    switch (info.type())
    {
        case DataCommInfo::UDP:
        {
            m_pDataComm = new UDPSocketComm(info);
        }
        break;

        case DataCommInfo::TCP:
        {

        }
        break;

        case DataCommInfo::CAN:
        {
            m_pDataComm = new CANSocketComm(info);
        }
        break;

        case DataCommInfo::COM:
        {
            m_pDataComm = new SerialPortComm(info);
        }
        break;

        default:
        break;
    }
    return  (m_pDataComm->init());
}

int CCommInterface::open()
{
    if(m_pDataComm == nullptr)
    {
        bool ret = init();
        if(!ret)
        {
            return (-1);
        }
    }
    return (m_pDataComm->open());
}

void CCommInterface::close()
{
    m_pDataComm->close();
}

bool CCommInterface::hasReadData()
{
    return (m_pDataComm->hasReadData());
}

qint64 CCommInterface::readData(QByteArray &data,qint64 maxSize,int timeOut)
{
    return (m_pDataComm->readData(data,maxSize,timeOut));
}

qint64 CCommInterface::writeData(QByteArray &data)
{
    return (m_pDataComm->writeData(data));
}
