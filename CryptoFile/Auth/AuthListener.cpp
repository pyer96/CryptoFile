#include "CryptoFile/Auth/AuthListener.hpp"

namespace auth {
AuthListener::AuthListener(
    std::string listen_uri,
    pplx::task_completion_event<bool> &task_completion_event)
    : m_listener{listen_uri}, m_task_completion_event{task_completion_event} {
  m_listener.support([this](web::http::http_request request) {
    auto params = web::uri::split_query(request.relative_uri().query());
    for (const auto &p : params) {
      std::cerr << "key = " << p.first << " value = " << p.second << '\n';
    }
    auto token = params.find("code");
    if (token != params.end()) {
      m_task_completion_event.set(true);
      m_authorization_token = params.find("code")->second;
      request.reply(web::http::status_codes::OK, U("Ok."));
    } else {
      m_task_completion_event.set(false);
      request.reply(web::http::status_codes::OK, U("An error occurred\n"));
    }
  });
  m_listener.open().wait();
}
} // namespace auth

