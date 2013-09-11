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
    FLAG_COMPRESSED = 0x00040000
  };

public:
  Record();

  void readFrom(std::istream &stream);

  bool flagSet(EFlag flag) const;

  const std::vector<uint8_t> &data() const { return m_Data; }

private:
  struct Header {
    char type[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
    uint16_t version;
    uint16_t padding;
  } m_Header;

  std::vector<uint8_t> m_Data;
};

}

#endif // RECORD_H
