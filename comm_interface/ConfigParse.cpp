#include "ConfigParse.h"

ConfigParse::ConfigParse()
    :m_bFileFinished(false),m_bAliasFinished(false),m_strFileName(""),m_strAlias("")
{

}

ConfigParse::ConfigParse(QString &file,QString &alias)
    :m_strFileName(""),m_strAlias("")
{
    if(file.trimmed().isEmpty())
    {
        qDebug("ConfigParse::ConfigParse @ the file name is empty!");
        return;
    }

    if(m_strAlias.trimmed().isEmpty())
    {
        qDebug("ConfigParse::ConfigParse @ the alias name is empty!");
        return;
    }

    m_strFileName = file;
    m_strAlias = alias;
    m_bFileFinished = true;
    m_bAliasFinished = true;
}

ConfigParse::~ConfigParse()
{

}

bool ConfigParse::parse()
{
    if(m_bFileFinished && m_bAliasFinished)
    {
        qDebug("ConfigParse::parse @ the parameter is invalid!");
        return false;
    }
    if(m_strFileName.trimmed().isEmpty())
    {
        qDebug("ConfigParse::parse @ the file name is empty!");
        return false;
    }

    if(m_strAlias.trimmed().isEmpty())
    {
        qDebug("ConfigParse::parse @ the alias name is empty!");
        return false;
    }

    QFile file(m_strFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray baSeed;
    while (!file.atEnd()) {
        QByteArray baLine = file.readLine();
        QByteArray baLineTemp = baLine.trimmed();
        if(baLineTemp.startsWith('#'))
            continue;
        QByteArray matchStr(m_strAlias.toStdString().c_str());
        if(baLineTemp.startsWith(matchStr))
        {
            baSeed = baLineTemp;
            break;
        }
    }
    file.close();

    QString strItem = QString(baSeed);
    QStringList lstItems = strItem.split(":");
    int nParamSize = lstItems.size();
    if(nParamSize != 4)
    {
        qDebug("ConfigParse::parse @ the item is invalid!");
        return false;
    }

    this->m_DataCommInfo.setFilterAlias(m_strAlias);

    //协议类型
    QString strProtoName = lstItems.at(1).trimmed().toUpper();
    if(strProtoName.isEmpty())
    {
        qDebug("ConfigParse::parse @ the protocol name is empty!");
        return false;
    }

    if(strProtoName == "TCP")
    {
         this->m_DataCommInfo.setProtoType(DataCommInfo::TCP);
    }
    else if(strProtoName == "UDP")
    {
         this->m_DataCommInfo.setProtoType(DataCommInfo::UDP);
    }
    else if(strProtoName == "CAN")
    {
         this->m_DataCommInfo.setProtoType(DataCommInfo::CAN);
    }
    else if(strProtoName == "COM")
    {
         this->m_DataCommInfo.setProtoType(DataCommInfo::COM);
    }
    else
    {
        qDebug("ConfigParse::parse @ the comm type is not supported!");
    }

    //设备名称
    QString strDevName = lstItems.at(2).trimmed();
    this->m_DataCommInfo.setDevName(strDevName);

    //通讯参数
    QString strProtoParam = lstItems.at(3).trimmed();
    this->m_DataCommInfo.setParam(strProtoParam);
    return true;
}

const DataCommInfo& ConfigParse::getCommInfo(bool *ok)
{
    *ok =  parse();
    return this->m_DataCommInfo;
}
