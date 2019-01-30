#ifndef __Service__Authenticator__
#define __Service__Authenticator__

#include <cpprest/http_listener.h>
#include <cpprest/oauth2.h>

#include <memory>

namespace session {
namespace auth {
using namespace web::http;
/** This class implements oauth2 functionalities for CPPRESTSDK and is used to
 * read the authorization token from redirect uri and trade it for an access
 * token. Reading is done with a handler added to a listener.
 */
class ServiceAuthenticator {

private:
  oauth2::experimental::oauth2_config m_oauth2_config;
  std::unique_ptr<experimental::listener::http_listener> m_listener;
  pplx::task_completion_event<bool> m_task_completion_event;
  std::mutex m_resplock;

public:
  ServiceAuthenticator(std::string auth_endpoint, std::string access_endpoint,
                       std::string client_id, std::string client_secrets,
                       std::string redirect_uri,
                       std::string scope = std::string());
  ~ServiceAuthenticator() { m_listener->close().wait(); }
  pplx::task<void> open() { return m_listener->open(); }
  pplx::task<void> close() { return m_listener->close(); }
  const auto &oauth2_config() const { return m_oauth2_config; }
};
} // namespace auth
} // namespace session
#endif
