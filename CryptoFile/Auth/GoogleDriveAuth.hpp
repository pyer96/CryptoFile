#include "CryptoFile/Auth/ServiceAuth.hpp"

#include <cpprest/uri_builder.h>

namespace auth {
class GoogleDriveAuth : public ServiceAuth {
public:
  GoogleDriveAuth()
      : ServiceAuth(
            web::http::uri_builder("https://accounts.google.com/o/oauth2/v2")
                .append_path("/auth")
                .append_query("client_id=548501522105-"
                              "nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
                              "googleusercontent.com")
                .append_query("response_type=code")
                .append_query("redirect_uri=http://localhost:8888/")
                .append_query(
                    "scope=https://www.googleapis.com/auth/drive.file"),
            "http://localhost:8888/")

  {}
};

} // namespace auth
