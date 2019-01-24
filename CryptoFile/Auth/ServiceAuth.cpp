#include "CryptoFile/Auth/ServiceAuth.hpp"
#include "Tools/OpenBrowser.hpp"

namespace auth {
ServiceAuth::ServiceAuth(web::uri_builder uri_builder, std::string redirect_uri)
    : m_listener{redirect_uri, m_task_complition_event} {
  get_authorization_token(uri_builder);
  if (not m_listener.authorization_token().empty()) {
    std::cerr << "Getting access token\n";
  }
}

void ServiceAuth::get_authorization_token(web::uri_builder uri_builder) {
  tools::open_browser(uri_builder.to_string());
  auto auth_task = pplx::create_task(m_task_complition_event);
  std::cerr << "task waiting...\n";
  auth_task.wait();
  std::cerr << "task ended\n";
  auto auth_token = m_listener.authorization_token();
  std::cerr << "auth_token = " << auth_token << '\n';
  m_listener.close().wait();
}

void ServiceAuth::get_access_token(){

}
} // namespace auth
