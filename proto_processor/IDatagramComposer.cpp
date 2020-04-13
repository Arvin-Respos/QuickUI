#include "IDatagramComposer.h"

IDatagramComposer::IDatagramComposer(QByteArray &data)
{
  Q_UNUSED(data)
}

IDatagramComposer::~IDatagramComposer()
{

}

QByteArray IDatagramComposer::data()
{
  return m_Datagram;
}

void IDatagramComposer::clear()
{

}
