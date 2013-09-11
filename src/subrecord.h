#ifndef SUBRECORD_H
#define SUBRECORD_H


#include <cstdint>
#include <istream>
#include <vector>


namespace ESP {


/**
 * @brief sub-record storage class without record-specific information
 */
class SubRecord
{
public:

  enum EType {
    TYPE_UNKNOWN,
    TYPE_HEDR,
    TYPE_CNAM,
    TYPE_SNAM,
    TYPE_MAST,
    TYPE_ONAM
  };

public:
  SubRecord();

  void readFrom(std::istream &stream);

  EType type() const { return m_Type; }
  const std::vector<uint8_t> &data() const { return m_Data; }

private:

  EType m_Type;
  std::vector<uint8_t> m_Data;
};

}

#endif // SUBRECORD_H
