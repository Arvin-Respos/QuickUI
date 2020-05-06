#ifndef STATION_TYPE_H
#define STATION_TYPE_H

#include <QtGlobal>

//行车方向
typedef enum TrainRunDirection
{
    TRAIN_RUN_UP = 0,     //上行
    TRAIN_RUN_DOWN      //下行
}TRAIN_RUN_DIRECT_t;

//站点状态
typedef enum StationStat
{
  NOTOPEN = 0,  //未开通
  OVERPASS,       //越站
  PASSED,           //已过站
  NOTARRIVED,  //经过但未到达
  CURRENT,       //当前站
  NEXT,                //下一站
  PREVIOUS      //前一站
}STATION_STATUS_t;

#define MAX_PADDING_LEN           (100)
#define MAX_EVENTNAME_LEN     (256)
#define MAX_TRAIN_NO_LEN          (20)

//拥挤度
typedef enum CongestnDegree
{
  SPARSE = 0,           //稀疏
  COMFORTABLE,  //舒适
  CROWD,                //拥挤
  OVERLOAD          //超载
}CONGEST_DEG_t;

//卫生间使用情况
typedef enum ToiletUsageInfo
{
  NOT_USED = 0,
  USED
}TOILET_USAGE_INFO_t;

//车厢信息结构
typedef struct CoachInfo
{
  quint8 m_nCoachNo;                                      //车厢序列号
  float m_fInnerTemp;                                       //车厢内温度
  CONGEST_DEG_t m_tCngstDeg;                  //拥挤度
  TOILET_USAGE_INFO_t m_tToiletUsing; //卫生间使用情况
}COACH_INFO_t;

//外部环境信息结构
typedef struct OuterEnvInfo
{
    float m_fOutsideTemp;                                //室外温度
}OUT_ENV_INFO_t;

//视频播放器参数
typedef struct MediaPlayerInfo
{
  quint32 m_nChannelNo;      //通道号
  quint8   m_nVolume;           //音量
}MEDIA_PLAYER_t;

//显示屏幕相关
typedef struct ScreenParam
{
  quint8 m_nLight;        //亮度
}DISPLAY_PARAM_t;

//列车参数
typedef struct TrainInfo
{
  quint8 m_nCoachCount;          //车厢个数
  char m_strTrainNO[MAX_TRAIN_NO_LEN]; //列车编号/名称
   float m_fTrainSpeed;                                  //车速
}TRAIN_INFO_t;

//基本信息
typedef struct basicReportStationInfo
{
  quint32 m_nStartIndex;            //起始站点
  quint32 m_nEndIndex;            //末尾站点
  quint32 m_nCurrentIndex;      //当前站点
  quint32 m_nNextIndex;          //下一站
  TRAIN_RUN_DIRECT_t m_tRunDirection;   //上下行
}BASIC_REPORT_INFO_t;

//报站信息
typedef struct ReportStationInfo
{
    BASIC_REPORT_INFO_t m_tBasicInfo;
    char m_strEventName[MAX_EVENTNAME_LEN];   //事件名称
    MEDIA_PLAYER_t  m_tMediaPlayerInfo;     //播放器相关包括音量等
    DISPLAY_PARAM_t m_tScreenParamInfo;   //显示参数，包括亮度
    TRAIN_INFO_t m_tTrainInfo;                      //列车信息
    OUT_ENV_INFO_t m_tOuterEnvInfo;          //列车外部环境信息
    COACH_INFO_t m_tCoachInfo;                  //当前车厢信息
}REPORT_INFO_t;

#endif // STATION_TYPE_H
