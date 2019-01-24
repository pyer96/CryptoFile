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
      uri_builder("https://www.dropbox.com/oauth2/authorize")
          .append_query(
              "client_id=pndw92faxm4lh7e"
              )
          .append_query("response_type=code")
          .append_query("redirect_uri=http://localhost:8888/")
          .to_string();

  Listener listener(redirect_uri);
  open_browser(uri);
  listener.open().wait();
  std::cerr << uri << '\n';

  std::string auth_token;
  std::getline(std::cin, auth_token);
  std::string body =
      "client_id=pndw92faxm4lh7e"
      "&client_secret=di82nja6vkt25ay"
      "&redirect_uri=http://localhost:8888/"
      "&grant_type=authorization_code&code=" +
      auth_token; 


  auto access_token_request = http_request(methods::POST);
  auto &h = access_token_request.headers();
  access_token_request.set_request_uri("/oauth2/token");
  h.set_content_type("application/x-www-form-urlencoded");
  access_token_request.set_body(body);

  std::cerr << "access_token_request :\n"
            << access_token_request.to_string() << '\n';

  web::http::client::http_client client("https://api.dropboxapi.com");
  client.request(access_token_request)
      .then([=](http_response response) {
    std::cerr << "\ntask = " << response.extract_string().get() <<'\n';
      })
    .wait();
 

  web::json::value arguments = web::json::value::object();
  arguments["path"] = web::json::value::string("/prova.txt");
  arguments["mode"]  = web::json::value::string("add");
  arguments["autorename"] = web::json::value::boolean(true);
  arguments["mute"] = web::json::value::boolean(false);
  arguments["strict_conflict"] = web::json::value::boolean(false);

  web::http::client::http_client upfile("https://content.dropboxapi.com");
  std::string access_token;
  std::getline(std::cin, access_token);
   auto drive_file_request = http_request(methods::POST);
   drive_file_request.set_request_uri("/2/files/upload");
   auto& head = drive_file_request.headers();
   head.add("Authorization","Bearer "+ access_token);
   head.set_content_type("application/octet-stream");
   head.add("Dropbox-API-Arg", arguments.serialize());
   std::cerr<<"request for file ---->"<<drive_file_request.to_string(); 
   
   upfile.request(drive_file_request).then ([=](http_response response)
           {
            std::cerr<< "json file list ---->>>" <<response.extract_string().get()<<'\n';
           }).wait();
   return 0;
}

