#include "CryptoFile/Session/Auth/ServiceAuthenticator.hpp"

#include "Tools/OpenBrowser.hpp"

namespace session {
namespace auth {
ServiceAuthenticator::ServiceAuthenticator(std::string auth_endpoint,
                                           std::string access_endpoint,
                                           std::string client_id,
                                           std::string client_secrets,
                                           std::string redirect_uri,
                                           std::string scope)
    : m_listener{redirect_uri}, m_oauth2_config{client_id,     client_secrets,
                                                auth_endpoint, access_endpoint,
                                                redirect_uri,  scope} {
  // Add handler to the listener that read the authorization token form the
  // redirect_uri and trade it for the access and refresh tokens.
  std::cerr << "BEFORE SUPPORT\n";
  m_listener.support([=](web::http::http_request request) -> void {
    if (request.request_uri().path() == U("/") &&
        not request.request_uri().query().empty()) {
      m_resplock.lock();
      m_oauth2_config.token_from_redirected_uri(request.request_uri())
          .then([this, request](pplx::task<void> token_task) -> void {
            try {
              token_task.wait();
              m_task_completion_event.set(true);
            } catch (const oauth2::experimental::oauth2_exception &e) {
              ucout << "Error: " << e.what() << std::endl;
              m_task_completion_event.set(false);
            }
          });
      request.reply(status_codes::OK, U("Ok."));
      m_resplock.unlock();
    } else {
      request.reply(status_codes::NotFound, U("Not found."));
    }
  });
  std::cerr << "AFTER SUPPORT\n";
  m_listener.open();
  std::cerr << "AFTER WAIT\n";

  // We ask the user's consent to access their storage service by
  // redirecting on the default browser to the access link for oauth2
  // authorization.

  // put the state as true to pass parameters as key=value
  auto auth_uri = m_oauth2_config.build_authorization_uri(true);
  tools::open_browser(auth_uri);
  auto task = pplx::create_task(m_task_completion_event);
  task.wait();
  try {
    if (task.is_done()) {
      task.get();
      std::cerr << "User succesfully authenticated\n";
    }
  } catch (pplx::invalid_operation &e) {
    std::cerr << e.what() << '\n';
  }
}
} // namespace auth
} // namespace session
