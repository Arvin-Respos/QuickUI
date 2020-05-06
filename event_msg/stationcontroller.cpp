#include "stationcontroller.h"

StaionController::StaionController()
  :m_bIsDirtyData(false)
{

}

StaionController::~StaionController()
{

}

void StaionController::mapToLine(QList<quint32>& list)
{
  m_bIsDirtyData = true;

  QMutexLocker locker(&m_Mutex);
  m_LineMap.clear ();
  quint32 index = 1;
  foreach(quint32 value,list)
    m_LineMap.insert (index++,value);

  m_nStationCount = static_cast<int>(index);

  m_bIsDirtyData= false;
}

quint32 StaionController::mapToLineIndex(quint32 stationCode)
{
  if(m_bIsDirtyData)
    return (INVALID_DATA);
  return m_LineMap.key(stationCode);
}

quint32 StaionController::mapToStationCode(quint32 stationIndex)
{
  if(m_bIsDirtyData)
    return (INVALID_DATA);
  return m_LineMap.value(stationIndex);
}

void StaionController::mapToOverpass(QByteArray &data)
{
  m_bIsDirtyData = true;
  QMutexLocker locker(&m_Mutex);
  m_OverPassMap.clear ();
  m_OverPassMap.resize (data.size () * BITS_PER_BYTE);
  for(int i = 0; i < data.size (); i++) {
      char element = data.at(i);
      for(int j = 0; j < BITS_PER_BYTE; j++)  {
          if((element & (1 << j )) >> j) {
              m_OverPassMap[i * BITS_PER_BYTE + j] = true;
            }else {
              m_OverPassMap[i * BITS_PER_BYTE + j] = false;
            }
        }
    }

  m_bIsDirtyData = false;
}

void StaionController::mapToOpenStation(QByteArray &data)
{
  m_bIsDirtyData = true;
  QMutexLocker locker(&m_Mutex);
  m_OpenStation.clear ();
  m_OpenStation.resize (data.size () * BITS_PER_BYTE);
  for(int i = 0; i < data.size (); i++) {
      char element = data.at(i);
      for(int j = 0; j < BITS_PER_BYTE; j++)  {
          if((element & (1 << j )) >> j) {
              m_OpenStation[i * BITS_PER_BYTE + j] = true;
            }else {
              m_OpenStation[i * BITS_PER_BYTE + j] = false;
            }
        }
    }

  m_bIsDirtyData = false;
}

bool StaionController::isOverPass(bool &Ok,int stationIndex)
{
  if(m_bIsDirtyData)
    Ok = false;
  Ok = true;
  return m_OverPassMap.at (stationIndex);
}

bool StaionController::isOpen(bool &Ok,int stationIndex)
{
  if(m_bIsDirtyData)
    Ok = false;
  Ok = true;
  return m_OpenStation.at (stationIndex);
}

quint32 StaionController::getPrevIndex(quint32 stationIndex)
{
  if(m_tDirection == TRAIN_RUN_UP) {
      if(stationIndex <= 0) {
          stationIndex = 0;
        }else{
          stationIndex --;
        }
    }else if(m_tDirection == TRAIN_RUN_DOWN) {
      if(stationIndex >= static_cast<quint32>(m_nStationCount)) {
          stationIndex = static_cast<quint32>(m_nStationCount);
        }else{
          stationIndex ++;
        }
    }
  return stationIndex;
}

quint32 StaionController::getNextIndex(quint32 stationIndex)
{
  if(m_tDirection == TRAIN_RUN_UP) {
      if(stationIndex >= static_cast<quint32>(m_nStationCount)) {
          stationIndex = static_cast<quint32>(m_nStationCount - 1);
        }else{
          stationIndex ++;
        }
    }else if(m_tDirection == TRAIN_RUN_DOWN) {
      if(stationIndex <= 0) {
          stationIndex = 0;
        }else{
          stationIndex --;
        }
    }
  return stationIndex;
}

STATION_STATUS_t StaionController::getStationStat(quint32 stationIndex)
{
  /**
    判定stationIndex指定的站点的状态，判定规则如下：
    如果是未开通则是未开通；
    如果是开通、已过站，且是前一站，则是前一站，否则是已过站
    如果是开通、等于当前站，为当前站；
    如果是开通、未过站、越站，则是越站
    如果是开通、未过站，等于下一站，且不越站，则是下一站；
    如果是开通、未过站，不等于下一站，且不越站，则将到站；
  */

  bool bOk = false;
  if((!isOpen(bOk,static_cast<int>(stationIndex)) && bOk) {
      if(stationIndex){

        }
    }else{
      return NOTOPEN;
    }
}
