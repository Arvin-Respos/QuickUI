#ifndef IDATAGRAMCOMPOSER_H
#define IDATAGRAMCOMPOSER_H

#include <QByteArray>

class IDatagramComposer
{
public:
  explicit IDatagramComposer(QByteArray &data);
  virtual ~IDatagramComposer();

public:
  bool isIntegrated() {
   return m_bIsPackageIntegrated;
 }
  void setIntegrated(bool value) {
    m_bIsPackageIntegrated = value;
  }

protected:
  virtual QByteArray data();
  virtual void clear();

protected:
  QByteArray m_Datagram;

private:
  bool m_bIsPackageIntegrated;
};

#endif // IDATAGRAMCOMPOSER_H
