#ifndef __Drive__Session__
#define __Drive__Session__

#include "CryptoFile/Session/ServiceSession.hpp"

#include <cpprest/uri_builder.h>

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
  virtual int upload_file(std::string file_path) override;
};
} // namespace session
#endif
