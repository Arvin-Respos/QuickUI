#ifndef DATACOMMADAPTER_H
#define DATACOMMADAPTER_H

#include <QByteArray>
#include <QString>

class ConfigParse;
class IDataComm;

class CCommInterface
{
public:
    explicit CCommInterface();
    CCommInterface(QString file,QString alias);
    ~CCommInterface();

public:
    void setFileName(QString &fileName){
        m_strFileName = fileName;
        m_bFileOk = true;
    }
    void setConnectAlias(QString &alias){
        m_strFileName = alias;
        m_bAliasOk = true;
    }

public:
    bool init();
    int open();
    void close();
    bool hasReadData();
    qint64 readData(QByteArray &data,qint64 maxSize = 1024,int timeOut = 1000);
    qint64 writeData(QByteArray &data);

private:
    bool m_bFileOk;
    bool m_bAliasOk;
    ConfigParse *m_pConfigParser;
    QString m_strFileName;
    QString m_strAlias;
    IDataComm *m_pDataComm;
};


#endif // DATACOMMADAPTER_H
