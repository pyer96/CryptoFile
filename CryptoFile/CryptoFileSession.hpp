#ifndef __CryptoFile__CryptoFile__Session__
#define __CryptoFile__CryptoFile__Session__

#include "CryptoFile/Db/CloudService.hpp"
#include "CryptoFile/Db/OriginalFile.hpp"
#include "CryptoFile/Session/ServiceSession.hpp"

#include <boost/filesystem/path.hpp>

namespace cryptofile {

class CryptoFileSession {
private:
  std::vector<std::unique_ptr<db::OriginalFile>> m_original_file;
  std::vector<std::unique_ptr<session::ServiceSession>> m_authenticated_clouds;
  CryptoFileSession(std::vector<db::CloudService> clouds_to_authenticate);

public:
  void list_original_files();
  void
  save_file_on_clouds(std::size_t section_number,
                      boost::filesystem::path file_path,
                      std::vector<db::CloudService> selected_clouds); // int
  void restore_file_from_clouds(
      std::size_t original_file_id,
      boost::filesystem::path restored_file_path = "/tmp/CryptoFile/");
};

} // namespace cryptofile

#endif
