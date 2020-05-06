#include "assetmanager.h"

AssetManager::AssetManager()
{
  m_singleString.clear ();
  m_MultiStr.clear();

    //图片
  m_singleImage.clear ();
  m_MultiImages.clear ();

    //颜色
  m_singleColor.clear ();
  m_MultiColors.clear ();

  init();
}

QVariant AssetManager::getResource(QString key,int index)
{
      QStringList strKey = key.split ("@");

      if(key.startsWith ("text@")) {

          return m_singleString.value (strKey.at (1));
        }else if(key.startsWith ("text-array@")) {

            return m_MultiStr.value (strKey.at (1)).at (index);
        }else if(key.startsWith ("image@")) {

            return m_singleImage.value (strKey.at (1));
        }else if(key.startsWith ("image-array@")) {

            return m_MultiImages.value (strKey.at (1)).at (index);
        }else if(key.startsWith ("color@")) {

            return m_singleImage.value (strKey.at (1));
        }else if(key.startsWith ("color-array@")) {

            return m_MultiImages.value (strKey.at (1)).at (index);
        }

       return "Undefine";
}

void AssetManager::initTexts(QString &strFileName)
{
      QFile file(strFileName);
      if(!file.exists ())
        return;

      if(!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
          qDebug("AssetManager::initTexts(QString &strFileName) failed!");
          return;
        }

      QXmlStreamReader xmlReader(&file);

      QList<QString> listText;
      QStringRef strAlias;
      while( ( !xmlReader.atEnd () ) && !( xmlReader.hasError () ) ) {

            QXmlStreamReader::TokenType type = xmlReader.readNext ();
            if(type == QXmlStreamReader::StartDocument)
                    continue;

            if(type == QXmlStreamReader::StartElement) {

                  QStringRef strRef = xmlReader.name();
                  QXmlStreamAttributes attributes = xmlReader.attributes ();

                  if( (strRef == "text") && (attributes.hasAttribute ("alias")) ) {

                      strAlias = attributes.value("alias");
//                     qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                      QString strText = xmlReader.readElementText ();
                      m_singleString.insert (strAlias.toString (), strText);
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                    } else if((strRef == "text-array") && (attributes.hasAttribute ("alias"))) {

                      strAlias = attributes.value("alias");
//                      qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                    }else if(strRef == "text") {

                      QString strText = xmlReader.readElementText ();
                      listText.append (strText);
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                    }
              }else if(type == QXmlStreamReader::EndElement) {

                    QStringRef strRefName = xmlReader.name ();
                    if(strRefName == "text-array") {
                          m_MultiStr.insert (strAlias.toString (),listText);
                          listText.clear ();
                      }
              }
        }
      file.close ();
      xmlReader.clear ();
/*
   for(QHash< QString,QString >::iterator begin = m_singleString.begin (); begin != m_singleString.end (); begin ++)
  {
        qDebug("first:%s\tsecond:%s",begin.key ().toStdString ().c_str (),begin.value ().toStdString ().c_str ());
   }

   for(QHash< QString,QList<QString> >::iterator begin = m_MultiStr.begin (); begin != m_MultiStr.end (); begin ++)
  {
        qDebug("alias:%s",begin.key ().toStdString ().c_str ());
        for(QList<QString>::iterator iter = begin.value ().begin (); iter != begin.value ().end (); iter ++)
       {
          qDebug("value:%s",iter->toStdString ().c_str ());
       }
   }
   */
}

void AssetManager::initImages(QString &strFileName)
{
  QFile file(strFileName);
  if(!file.exists ())
    return;

  if(!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug("AssetManager::initTexts(QString &strFileName) failed!");
      return;
    }

  QXmlStreamReader xmlReader(&file);

  QList<QUrl> listImages;
  QStringRef strAlias;
  while( ( !xmlReader.atEnd () ) && !( xmlReader.hasError () ) ) {

        QXmlStreamReader::TokenType type = xmlReader.readNext ();
        if(type == QXmlStreamReader::StartDocument)
                continue;

        if(type == QXmlStreamReader::StartElement) {

              QStringRef strRef = xmlReader.name();
              QXmlStreamAttributes attributes = xmlReader.attributes ();

              if( (strRef == "image") && (attributes.hasAttribute ("alias")) ) {

                  strAlias = attributes.value("alias");
//                     qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                  QString strText = xmlReader.readElementText ();
                  m_singleImage.insert (strAlias.toString (), strText);
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                } else if((strRef == "image-array") && (attributes.hasAttribute ("alias"))) {

                  strAlias = attributes.value("alias");
//                      qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                }else if(strRef == "image") {

                  QString strText = xmlReader.readElementText ();
                  listImages.append (QUrl(strText));
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                }
          }else if(type == QXmlStreamReader::EndElement) {

                QStringRef strRefName = xmlReader.name ();
                if(strRefName == "image-array") {
                      m_MultiImages.insert (strAlias.toString (),listImages);
                      listImages.clear ();
                  }
          }
    }
  file.close ();
  xmlReader.clear ();
}

void AssetManager::initColors(QString &strFileName)
{
  QFile file(strFileName);
  if(!file.exists ())
    return;

  if(!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug("AssetManager::initTexts(QString &strFileName) failed!");
      return;
    }

  QXmlStreamReader xmlReader(&file);

  QList<QColor> listColor;
  QStringRef strAlias;
  while( ( !xmlReader.atEnd () ) && !( xmlReader.hasError () ) ) {

        QXmlStreamReader::TokenType type = xmlReader.readNext ();
        if(type == QXmlStreamReader::StartDocument)
                continue;

        if(type == QXmlStreamReader::StartElement) {

              QStringRef strRef = xmlReader.name();
              QXmlStreamAttributes attributes = xmlReader.attributes ();

              if( (strRef == "color") && (attributes.hasAttribute ("alias")) ) {

                  strAlias = attributes.value("alias");
//                     qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                  QString strText = xmlReader.readElementText ();
                  m_singleString.insert (strAlias.toString (), strText);
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                } else if((strRef == "color-array") && (attributes.hasAttribute ("alias"))) {

                  strAlias = attributes.value("alias");
//                      qDebug("strAlias:%s",strAlias.toString ().toStdString ().c_str ());

                }else if(strRef == "color") {

                  QString strText = xmlReader.readElementText ();
                  QColor colorTemp;
                  colorTemp.setNamedColor (strText);
                  listColor.append (colorTemp);
//                      qDebug("text:%s",strText.toStdString ().c_str ());

                }
          }else if(type == QXmlStreamReader::EndElement) {

                QStringRef strRefName = xmlReader.name ();
                if(strRefName == "color-array") {
                      m_MultiColors.insert (strAlias.toString (),listColor);
                      listColor.clear ();
                  }
          }
    }
  file.close ();
  xmlReader.clear ();
}

void AssetManager::init()
{
    //解析配置文件
//  QString dirPath = QString::fromLocal8Bit (qgetenv ("RESFILE_DIR"));


  //解析文本资源
  QString txtFile = /*dirPath + */"string.xml";
  initTexts(txtFile);

  //解析图片资源
//  QString imageFile = dirPath + "image/image.xml";
//  initImages(imageFile);

  //解析颜色资源
//  QString colorFile = dirPath + "color/color.xml";
//  initColors(colorFile);
}
