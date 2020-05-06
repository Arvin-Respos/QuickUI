#ifndef STATIONCONTROLLER_H
#define STATIONCONTROLLER_H

#include <QBitArray>
#include <QHash>
#include <QMutexLocker>
#include "station_type.h"

#define INVALID_DATA      (99999)
#define BITS_PER_BYTE    (8)

//站点序号与线路站点之间的映射处理类
class StaionController
{
public:
  static StaionController& getInstance() {
      static StaionController  _instance;
      return _instance;
  }

public:
  ~StaionController();
  StaionController(const StaionController&) = delete;
  StaionController& operator=(const StaionController&) = delete;
  STATION_STATUS_t getStationStat(quint32 stationIndex);

private:
  StaionController();

public:
  void setBasicReportInfo(BASIC_REPORT_INFO_t *info) {
    m_tBasicReportInfo.m_nStartIndex = info->m_nStartIndex;
    m_tBasicReportInfo.m_nEndIndex = info->m_nEndIndex;
    m_tBasicReportInfo.m_nCurrentIndex = info->m_nCurrentIndex;
    m_tBasicReportInfo.m_nNextIndex = info->m_nNextIndex;
    m_tBasicReportInfo.m_tRunDirection = info->m_tRunDirection;
  }
  void mapToLine(QList<quint32>& list);                 //把下发的真实站点添加到线路中，形成映射
  quint32 mapToLineIndex(quint32 stationCode);     //把站点ID映射成线路中的站点序号
  quint32 mapToStationCode(quint32 stationIndex); //把站点序号映射成线路中的真实站点ID
  void mapToOverpass(QByteArray &data);           //越站设置
  void mapToOpenStation(QByteArray &data);     //开通站点设置
  bool isOverPass(bool &Ok,int stationIndex);        //是否越站
  bool isOpen(bool& Ok,int stationIndex);              //是否开通
  quint32 getPrevIndex(quint32 stationIndex);
  quint32 getNextIndex(quint32 stationIndex);

private:
  QHash<quint32,quint32> m_LineMap; //线路站点
  QBitArray m_OverPassMap;                //越站
  QBitArray m_OpenStation;                   //开通站点


  QMutex m_Mutex;
  bool m_bIsDirtyData;                          //脏数据标志

  BASIC_REPORT_INFO_t m_tBasicReportInfo;      //上下行
  int m_nStationCount;                                    //站点个数
};
#endif // STATIONCONTROLLER_H
