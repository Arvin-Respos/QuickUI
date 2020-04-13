#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H

#include <QFile>
#include <QTextStream>
#include "DataCommProtoType.h"

class ConfigParse
{
public:
    ConfigParse();
    ConfigParse(QString &file,QString &alias);
    ~ConfigParse();

public:
    void setFile(QString &file){
        m_strFileName = file;
        m_bFileFinished = true;
    }
    void setAlias(QString &alias) {
        m_strAlias = alias;
        m_bAliasFinished = true;
    }
    const DataCommInfo &getCommInfo(bool *ok);

private:
    bool parse();


private:
    bool m_bFileFinished;
    bool m_bAliasFinished;
    QString m_strFileName;
    QString m_strAlias;
    DataCommInfo m_DataCommInfo;
};


#endif // CONFIGPARSE_H
