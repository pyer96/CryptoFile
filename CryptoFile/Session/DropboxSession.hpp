#ifndef __Dropbox__Session__
#define __Dropbox__Session__

#include "CryptoFile/Auth/ServiceAuth.hpp"

namespace auth {
class DropboxSession : public ServiceAuth {
public:
  DropboxSession()
      : ServiceAuth{"https://www.dropbox.com/oauth2/authorize",
                    "https://api.dropboxapi.com", "pndw92faxm4lh7e",
                    "di82nja6vkt25ay", "http://localhost:8888/"} {}
};

} // namespace auth

#endif

