#ifndef DATAGRAMCOMPOSERGLINKMAP_H
#define DATAGRAMCOMPOSERGLINKMAP_H

#include <QtCore/QObject>
#include <QByteArray>

#include "IDatagramComposer.h"

class DatagramComposerGLinkMap : public IDatagramComposer
{
public:
  explicit DatagramComposerGLinkMap(QByteArray& data);
  ~DatagramComposerGLinkMap();

protected:
  virtual QByteArray data();
  virtual void clear();
};

#endif // DATAGRAMCOMPOSERGLINKMAP_H
