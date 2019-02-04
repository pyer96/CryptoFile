#ifndef __Original__File__
#define __Original__File__
#include <string>

namespace db {
class OriginalFile {
private:
  int m_original_file_id;
  std::string m_checksum;
  std::string m_name;

public:
  OriginalFile() {}
  auto id() const { return m_original_file_id; }
  const auto &checksum() const { return m_checksum; }
  const auto &name() const { return m_name; }
  void set_checksum(std::string checksum) { m_checksum = checksum; }
  void set_name(std::string name) { m_name = name; }
  void save();
};

} // namespace db
#endif

