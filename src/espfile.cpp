#include "espfile.h"
#include "subrecord.h"
#include "espexceptions.h"
#include <sstream>


ESP::File::File(const std::string &fileName)
{
  m_File.open(fileName, std::fstream::in | std::fstream::binary);
  init();
}

ESP::File::File(const std::wstring &fileName)
{
  m_File.open(fileName, std::fstream::in | std::fstream::binary);
  init();
}


class membuf : public std::basic_streambuf<char>
{
public:
  membuf(const char *start, size_t size) {
    // baad me! this is intended for an istream only so we're not modifying
    char *startMod = const_cast<char*>(start);
    setg(startMod, startMod, startMod + size);
  }
};


void ESP::File::init()
{
  if (!m_File.is_open()) {
    throw ESP::InvalidFileException("file not found");
  }
  m_File.exceptions(std::ios_base::badbit);

  uint8_t type[4];
  if (!m_File.read(reinterpret_cast<char*>(type), 4)) {
    throw ESP::InvalidFileException("file incomplete");
  }
  if (memcmp(type, "TES4", 4) != 0) {
    throw ESP::InvalidFileException("invalid file type");
  }
  m_File.seekg(0);

  m_MainRecord = readRecord();

  const std::vector<uint8_t> &data = m_MainRecord.data();
  membuf buf(reinterpret_cast<const char*>(&data[0]), data.size());

  std::istream stream(&buf);
  while (!stream.eof()) {
    SubRecord rec;
    bool success = rec.readFrom(stream);
    if (success) {
      if (rec.type() == SubRecord::TYPE_HEDR) {
        if (rec.data().size() != sizeof(m_Header)) {
          printf("invalid header size\n");
          m_Header.version = 0.0f;
          m_Header.numRecords = 1; // prevent this esp appear like a dummy
        } else {
          memcpy(&m_Header, &rec.data()[0], sizeof(m_Header));
        }
      } else if ((rec.type() == SubRecord::TYPE_MAST) && (rec.data().size() > 0)) {
        m_Masters.insert(reinterpret_cast<const char*>(&rec.data()[0]));
      }
    }
  }
}


ESP::Record ESP::File::readRecord()
{
  ESP::Record rec;
  rec.readFrom(m_File);
  return rec;
}

bool ESP::File::isMaster() const
{
  return m_MainRecord.flagSet(Record::FLAG_MASTER);
}

bool ESP::File::isDummy() const
{
  return m_Header.numRecords == 0;
}
