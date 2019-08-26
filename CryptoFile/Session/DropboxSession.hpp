#ifndef __CryptoFile__Session__Dropbox__Session__
#define __CryptoFile__Session__Dropbox__Session__

#include "CryptoFile/Session/ServiceSession.hpp"

namespace cryptofile {
namespace session {
class DropboxSession : public ServiceSession {
public:
  DropboxSession()
      : ServiceSession{db::CloudService::Dropbox,
                       "https://www.dropbox.com/oauth2/authorize",
                       "https://api.dropboxapi.com/oauth2/token",
                       "pndw92faxm4lh7e",
                       "di82nja6vkt25ay",
                       "http://localhost:8888/"} {}
  virtual web::json::value upload_file(std::vector<std::uint8_t> file_data,
                                       std::string file_name) override;
  std::vector<std::uint8_t> download_file(std::string cloud_file_id);
};

} // namespace session
} // namespace cryptofile
#endif

