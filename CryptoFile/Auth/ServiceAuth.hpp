#include "CryptoFile/Auth/AuthListener.hpp"

namespace auth {
class ServiceAuth {
private:
  AuthListener m_listener;
  pplx::task_completion_event<bool> m_task_complition_event;
  std::string m_access_token;
  std::string m_refresh_token;

public:
  ServiceAuth(web::http::uri_builder uri_builder, std::string redirect_uri);
  void get_authorization_token(web::uri_builder uri_builder);
  void get_access_token();
  const auto &access_token() { return m_access_token; }
};
} // namespace auth

