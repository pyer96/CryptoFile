#ifndef __Dropbox__Session__
#define __Dropbox__Session__

#include "CryptoFile/Session/ServiceSession.hpp"

namespace session {
class DropboxSession : public ServiceSession {
public:
  DropboxSession()
      : ServiceSession{"https://www.dropbox.com/oauth2/authorize",
                       "https://api.dropboxapi.com/oauth2/token", "pndw92faxm4lh7e",
                       "di82nja6vkt25ay", "http://localhost:8888/"} {}
  virtual int upload_file(std::string file_path) override;
};

} // namespace session

#endif

