#ifndef RECORD_H
#define RECORD_H

#include <cstdint>
#include <vector>
#include <istream>


namespace ESP {

/**
 * @brief record storage class without record-specific information
 */
class Record
{
public:
  enum EFlag {
    FLAG_MASTER = 0x00000001,
    FLAG_LIGHT_ALTERNATE = 0x00000100,
    FLAG_LIGHT = 0x00000200,
    FLAG_OVERRIDE = 0x00000200,
    FLAG_COMPRESSED = 0x00040000
  };

public:
  Record();

  bool readFrom(std::istream &stream);

  bool flagSet(EFlag flag) const;

  const std::vector<uint8_t> &data() const { return m_Data; }

private:
  struct Header {
    char type[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
  } m_Header;

  std::vector<uint8_t> m_Data;

  bool m_OblivionStyle;

};

}

#endif // RECORD_H
