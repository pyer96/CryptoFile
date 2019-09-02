#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/oauth2.h>
#include <cpprest/uri_builder.h>
#include <iostream>

using namespace web::http;
static void open_browser(utility::string_t auth_uri) {
  utility::string_t browser_cmd(U("xdg-open \"") + auth_uri + U("\""));
  (void)system(browser_cmd.c_str());
}

class Listener {
public:
  Listener(std::string redirect_uri) : m_listener(redirect_uri) {
    m_listener.support([=](http_request request) {
      auto relative_uri = request.relative_uri().to_string();
      m_token = relative_uri.find("code=");
      std::cerr << m_token << '\n';
      std::cerr << "relative_uri = " << relative_uri << '\n';
      request.reply(status_codes::OK, U("Ok."));
    });
  }
  ~Listener() { m_listener.close().wait(); }
  pplx::task<void> open() { return m_listener.open(); }
  pplx::task<void> close() { return m_listener.close(); }

private:
  experimental::listener::http_listener m_listener;
  std::string m_token;
};

int main() {
  auto redirect_uri = "http://localhost:8888/";

  auto uri =
      uri_builder("https://accounts.google.com/o/oauth2/v2")
          .append_path("/auth")
          .append_query(
              "client_id=548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
              "googleusercontent.com")
          .append_query("response_type=code")
          .append_query("redirect_uri=http://localhost:8888/")
          .append_query("scope=https://www.googleapis.com/auth/drive.file")
          .to_string();

  Listener listener(redirect_uri);
  open_browser(uri);
  listener.open().wait();
  std::cerr << uri << '\n';

  std::string auth_token;
  std::getline(std::cin, auth_token);
  std::string body =
      "client_id=548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
      "googleusercontent.com&client_secret=onrSqOp1gpwr64nn6hu_"
      "vfCQ&redirect_uri=http://"
      "localhost:8888/&grant_type=authorization_code&code=" +
      auth_token;
  /*
    std::string post_request(
        "POST /oauth2/v4/token HTTP/1.1 "
        "Host: www.googleapis.com "
        "Content-Type: application/x-www-form-urlencoded "
        "client_id=548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
        "googleusercontent.com&"
        "client_secret=onrSqOp1gpwr64nn6hu_vfCQi"
        "redirect_uri=http://localhost::8889&"
        "grant_type=authorization_code&code=");
    post_request += auth_token;
    std::cout << post_request << '\n';
  */
  auto access_token_request = http_request(methods::POST);
  auto &h = access_token_request.headers();
  access_token_request.set_request_uri("/oauth2/v4/token");
  h.set_content_type("application/x-www-form-urlencoded");
  // h.add("Host", "www.googleapis.com");
  access_token_request.set_body(body);
  /*
  h.add("client_id", "548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
                     "googleusercontent.com");
  h.add("client_secret", "onrSqOp1gpwr64nn6hu_vfCQi");
  h.add("redirect_uri", "http://localhost:8889");
  h.add("grant_type", "authorization_code");
  h.add("code", auth_token);
*/
  std::cerr << "access_token_request :\n"
            << access_token_request.to_string() << '\n';

  web::http::client::http_client client("https://www.googleapis.com");
  client.request(access_token_request)
      .then([=](http_response response) {
        std::cerr << "\ntask = " << response.extract_string().get() << '\n';
      })
      .wait();
  /*
  std::string auth_token;
  std::getline(std::cin, auth_token);
  std::cerr << "auth_token = " << auth_token << '\n';
    web::http::client::http_client
    client("https://www.googleapis.com/oauth2/v4"); auto
    access_token_uri_request = uri_builder("/token")
  .append_query(auth_token) .append_query(
                "client_id=548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
                "googleusercontent.com")
            .append_query("client_secrets=onrSqOp1gpwr64nn6hu_vfCQi")
            .append_query("redirect_uri=http://localhost:8889/")
            .append_query("grant_type=authorization_code");
  auto access_token_uri_request =
      uri_builder("https://www.googleapis.com/oauth2/v4")
          .append_path("/token")
          .append_query(auth_token)
          .append_query(
              "client_id=548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
              "googleusercontent.com")
          .append_query("client_secrets=onrSqOp1gpwr64nn6hu_vfCQi")
          .append_query("redirect_uri=http://localhost:8889/")
          .append_query("grant_type=authorization_code");

  Listener listener2("http://localhost:8889/");
  open_browser(access_token_uri_request.to_string());

  //  client.request(methods::GET, access_token_uri_request.to_string());
  listener2.open().wait();
  */

  return 0;
}

