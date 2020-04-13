#ifndef DATACOMMPROTOTYPE_H
#define DATACOMMPROTOTYPE_H

#define MAX_COMM_TYPE     (10)

#include <QString>

/**
 * @brief The DataCommInfo class
 */
class DataCommInfo
{
public:
  explicit DataCommInfo() {
    m_strAlias = "";
    m_type = MAX;
    m_strDevName = "";
    m_strParam = "";
  }

  DataCommInfo(const DataCommInfo &info) {
    m_strAlias = info.m_strAlias;
    m_type = info.m_type;
    m_strDevName = info.m_strDevName;
    m_strParam = info.m_strParam;
  }

  /**
   * @brief The ProtoType enum
   *  \a通讯类型.当前支持UDP,TCP,socket CAN及串口
   */
  enum  ProtoType
  {
      UDP = 0,
      TCP,
      CAN,
      COM,
      MAX = MAX_COMM_TYPE
  };
 typedef enum  ProtoType PROTO_TYPE;


  DataCommInfo(QString &strAlias,PROTO_TYPE type,QString strDevName,QString strParam) {
    m_strAlias = strAlias;
    m_type = type;
    m_strDevName = strDevName;
    m_strParam = strParam;
  }

  void setProtoType(PROTO_TYPE type) {
    m_type = type;
  }
  void setFilterAlias(QString &strAlias) {
    m_strAlias = strAlias;
  }

  void setParam(QString &strParam) {
    m_strParam = strParam;
  }
  void setDevName(QString &strDevName) {
    m_strDevName = strDevName;
  }

public:
  DataCommInfo & operator= (DataCommInfo &info) {
      m_strAlias = info.m_strAlias;
      m_type = info.m_type;
      m_strDevName = info.m_strDevName;
      m_strParam = info.m_strParam;
      return *this;
  }

  QString alias() {
      return m_strAlias;
  }

  QString devName() {
      return m_strDevName;
  }

  QString parameter() {
      return m_strParam;
  }

    PROTO_TYPE type(){
      return m_type;
  }

private:
  QString m_strAlias;
  PROTO_TYPE m_type;
  QString m_strDevName;
  QString m_strParam;
};


#endif // DATACOMMPROTOTYPE_H
