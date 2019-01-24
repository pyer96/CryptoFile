#include <cpprest/http_listener.h>

namespace auth {
class AuthListener {
private:
  web::http::experimental::listener::http_listener m_listener;
  std::string m_authorization_token;
  pplx::task_completion_event<bool> &m_task_completion_event;

public:
  AuthListener(std::string listen_uri,
               pplx::task_completion_event<bool> &task_complition_event);
  pplx::task<void> open() { return m_listener.open(); }
  pplx::task<void> close() { return m_listener.close(); }
  const auto &authorization_token() { return m_authorization_token; }
};
} // namespace auth
