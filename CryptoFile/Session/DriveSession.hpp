#ifndef __CryptoFile__Session__Drive__Session__
#define __CryptoFile__Session__Drive__Session__

#include "CryptoFile/Session/ServiceSession.hpp"

#include <cpprest/uri_builder.h>

namespace cryptofile {
namespace session {
class DriveSession : public ServiceSession {
public:
  DriveSession()
      : ServiceSession{
            "https://accounts.google.com/o/oauth2/v2/auth",
            "https://www.googleapis.com/oauth2/v4/token",
            "548501522105-"
            "nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
            "googleusercontent.com",
            "onrSqOp1gpwr64nn6hu_vfCQ",
            "http://localhost:8889/",
            "https://www.googleapis.com/auth/drive",
        } {}
  virtual web::json::value upload_file(std::vector<std::uint8_t> file_data,
                                       std::string file_name) override;
  std::vector<std::uint8_t> download_file(std::string cloud_file_id);
};
} // namespace session
} // namespace cryptofile
#endif
