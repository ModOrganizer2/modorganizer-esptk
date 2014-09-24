#include "subrecord.h"
#include "esptypes.h"
#include "espexceptions.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <boost/assign.hpp>


using namespace boost::assign;


ESP::SubRecord::SubRecord()
  : m_Type(TYPE_UNKNOWN)
  , m_Data()
{
}


bool ESP::SubRecord::readFrom(std::istream &stream)
{
  static std::unordered_map<std::string, EType> s_TypeMap = map_list_of("HEDR", TYPE_HEDR)
                                                                       ("CNAM", TYPE_CNAM)
                                                                       ("MAST", TYPE_MAST)
                                                                       ("ONAM", TYPE_ONAM)
                                                                       ("SNAM", TYPE_SNAM);

  char typeString[5];
  if (!stream.read(typeString, 4)) {
    if (stream.gcount() == 0) {
      return false;
    } else {
      throw ESP::InvalidRecordException("sub-record incomplete");
    }
  }
  if (stream.gcount() != 4) {
    throw ESP::InvalidRecordException("sub-record type incomplete");
  }
  typeString[4] = '\0'; // not sure if this is required, shouldn't be
  auto iter = s_TypeMap.find(std::string(typeString));
  if (iter != s_TypeMap.end()) {
    m_Type = iter->second;
  } else {
    m_Type = TYPE_UNKNOWN;
  }

  uint16_t dataSize = readType<uint16_t>(stream);

  m_Data.resize(dataSize);

  stream.read(reinterpret_cast<char*>(&m_Data[0]), dataSize);
  if (!stream) {
    throw ESP::InvalidRecordException("sub-record incomplete");
  }
  return true;
}
