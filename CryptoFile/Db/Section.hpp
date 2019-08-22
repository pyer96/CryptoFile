#ifndef __CryptoFile__Db__Section__
#define __CryptoFile__Db__Section__

#include <string>

namespace cryptofile {
namespace db {
class Section {
private:
  int m_section_id;
  int m_original_file_id;
  std::string m_name;
  int m_order;
  int m_cloud_service_id;
  std::string m_section_cloud_id;

public:
  Section() {}
  auto id() const { return m_section_id; }
  auto original_file_id() const { return m_original_file_id; }
  const auto &name() const { return m_name; }
  auto order() const { return m_order; }
  auto cloud_service_id() const { return m_cloud_service_id; }
  auto section_cloud_id() const { return m_section_cloud_id; }
  void set_original_file_id(int original_file_id) {
    m_original_file_id = original_file_id;
  }
  void set_id(int section_id) { m_section_id = section_id; }
  void set_name(std::string name) { m_name = name; }
  void set_order(int order) { m_order = order; }
  void set_cloud_service_id(int cloud_service_id) {
    m_cloud_service_id = cloud_service_id;
  }
  void set_section_cloud_id(std::string section_cloud_id) {
    m_section_cloud_id = section_cloud_id;
  }
  void save();
  void print_members();
};
} // namespace db
} // namespace cryptofile
#endif
