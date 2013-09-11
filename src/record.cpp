#include "record.h"


ESP::Record::Record()
{

}

bool ESP::Record::flagSet(ESP::Record::EFlag flag) const
{
  return (m_Header.flags & flag) != 0;
}

void ESP::Record::readFrom(std::istream &stream)
{
  stream.read(reinterpret_cast<char*>(&m_Header), sizeof(Header));
  m_Data.resize(m_Header.dataSize);
  stream.read(reinterpret_cast<char*>(&m_Data[0]), m_Header.dataSize);
}
