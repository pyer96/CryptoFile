#ifndef __Service__Session__
#define __Service__Session__

#include "CryptoFile/Session/Auth/ServiceAuthenticator.hpp"

#include <cpprest/http_client.h>

namespace session {
using namespace web::http;
class ServiceSession {
private:
  auth::ServiceAuthenticator m_service_authenticator;
  client::http_client_config m_http_client_config;

public:
  ServiceSession(std::string auth_endpoint, std::string access_endpoint,
                 std::string client_id, std::string client_secrets,
                 std::string redirect_uri, std::string scope = std::string());
  virtual ~ServiceSession() {}
  const auto &http_client_config() const { return m_http_client_config; }
  virtual int upload_file(std::string file_path) = 0;
};
} // namespace session

#endif
