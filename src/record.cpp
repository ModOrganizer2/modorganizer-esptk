#include "record.h"
#include "espexceptions.h"

ESP::Record::Record() : m_Header(), m_Data(), m_OblivionStyle(false) {}

bool ESP::Record::flagSet(ESP::Record::EFlag flag) const
{
  return (m_Header.flags & flag) != 0;
}

bool ESP::Record::readFrom(std::istream& stream)
{
  if (!stream.read(reinterpret_cast<char*>(&m_Header), sizeof(Header))) {
    if (stream.gcount() == 0) {
      return false;
    } else {
      throw ESP::InvalidRecordException("record incomplete");
    }
  }

  char buf[4];
  stream.read(buf, 4);
  if (memcmp(buf, "HEDR", 4) == 0) {
    m_OblivionStyle = true;
    stream.seekg(-4, std::istream::cur);
  }  // skyrim has some version data here I don't know how to interpret anyway

  m_Data.resize(m_Header.dataSize);
  stream.read(reinterpret_cast<char*>(&m_Data[0]), m_Header.dataSize);
  if (!stream) {
    throw ESP::InvalidRecordException("record incomplete");
  }
  return true;
}
