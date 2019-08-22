#ifndef __CryptoFile__Db__Original__File__
#define __CryptoFile__Db__Original__File__
#include <string>

namespace cryptofile {
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
  void set_id(int original_file_id) { m_original_file_id = original_file_id; }
  void set_checksum(std::string checksum) { m_checksum = checksum; }
  void set_name(std::string name) { m_name = name; }
  void save();
  void print_members();
};

} // namespace db
} // namespace cryptofile
#endif

