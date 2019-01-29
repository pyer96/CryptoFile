#include "CryptoFile/Session/ServiceSession.hpp"

namespace session {

ServiceSession::ServiceSession(std::string auth_endpoint,
                               std::string access_endpoint,
                               std::string client_id,
                               std::string client_secrets,
                               std::string redirect_uri, std::string scope)
    : m_service_authenticator{auth_endpoint,  access_endpoint, client_id,
                              client_secrets, redirect_uri,    scope} {
  m_http_client_config.set_oauth2(m_service_authenticator.oauth2_config());
}
} // namespace session
