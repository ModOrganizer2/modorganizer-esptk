#ifndef ESPFILE_H
#define ESPFILE_H


#include <string>
#include <fstream>
#include <set>
#include "record.h"


namespace ESP {


class File
{
public:

  File(const std::string &fileName);
  File(const std::wstring &fileName);

  Record readRecord();

  bool isMaster() const;
  bool isDummy() const;
  std::set<std::string> masters() const { return m_Masters; }

private:

  void init();

private:

  std::ifstream m_File;

  struct {
    float version;
    int32_t numRecords;
    uint32_t nextObjectId;
  } m_Header;

  Record m_MainRecord;
  std::set<std::string> m_Masters;

};

}

#endif // ESPFILE_H
