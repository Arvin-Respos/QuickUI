#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QtCore/QObject>
#include <QHash>
#include <QString>
#include <QUrl>
#include <QList>
#include <QColor>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QStringRef>

class AssetManager
{
public:
  ~AssetManager() {
  }
  /**
   * @brief getResource
   * @param key       获取资源时使用的关键名，以"aaa@bbb"的方式进行,"aaa"可以是如下取值：
   *        text  表示取文本资源；image表示取图片资源；color表示取颜色资源
   *        bbb为配置文件中的alias
   * @param index  当需要获取组资源的时候，会把组中序号为index的那一个取出来，默认为0
   * @return 返回文本内容、颜色值、图片路径等
   */
  QVariant getResource(QString key,int index = 0);

private:
  AssetManager();
  void init();
  void initTexts(QString &strFileName);
  void initImages(QString &strFileName);
  void initColors(QString &strFileName);

 public:
  static AssetManager &getInstance(){
      static AssetManager _instance;
      return _instance;
  }

 private:
  //文本
  QHash<QString,QString> m_singleString;        //可变的单字符串资源
  QHash<QString,QList<QString> > m_MultiStr;      //可变的字符串列表资源

  //图片
  QHash<QString,QUrl> m_singleImage;        //可变的单图片文件资源
  QHash<QString,QList<QUrl> > m_MultiImages;        //可变的图片组文件资源

  //颜色
  QHash<QString,QColor> m_singleColor;        //可变的单颜色文件资源
  QHash< QString,QList<QColor> > m_MultiColors;        //可变的颜色组文件资源
};

#endif // ASSETMANAGER_H
