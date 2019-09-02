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

class DriveSession {
private:
  oauth2::experimental::oauth2_config m_oauth2_config;
  //  client::http_client m_http_client;
  std::unique_ptr<experimental::listener::http_listener> m_listener;
  std::mutex m_resplock;
  // client::http_client_config m_http_client_congif;
  pplx::task_completion_event<bool> m_task_completion_event;

public:
  DriveSession(utility::string_t client_key, utility::string_t client_secret,
               utility::string_t auth_endpoint,
               utility::string_t token_endpoint, utility::string_t redirect_uri,
               utility::string_t scope /*, utility::string_t base_uri*/)
      : m_oauth2_config{client_key,     client_secret, auth_endpoint,
                        token_endpoint, redirect_uri,  scope},
        /* m_http_client{base_uri}, */
        m_listener{new experimental::listener::http_listener(redirect_uri)} {
    std::cerr << "listener support\n";
    m_listener->support([=](web::http::http_request request) -> void {
      std::cerr << "listener support\n";
      if (request.request_uri().path() == U("/") &&
          request.request_uri().query() != U("")) {
        m_resplock.lock();
        std::cerr
            << "m_oauth2_config.token_from_redirected_uri\tredirect_uri = "
            << request.request_uri().query() << '\n';
        m_oauth2_config.token_from_redirected_uri(request.request_uri())
            .then([this, request](pplx::task<void> token_task) -> void {
              try {
                token_task.wait();
                m_task_completion_event.set(true);
                std::cerr << "oauth access token = "
                          << m_oauth2_config.access_token_key() << '\n';
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
    std::cerr << "\tm_listener->open().wait()\n";
    m_listener->open().wait();
  }

  ~DriveSession() { m_listener->close().wait(); }

  void run() {
    auto auth_uri = m_oauth2_config.build_authorization_uri(true);
    std::cerr << auth_uri << '\n';
    open_browser(auth_uri);
    std::cerr << "pplx::create_task(m_task_completion_event).get()\n";
    auto task = pplx::create_task(m_task_completion_event);
    task.wait();
    std::cerr << "task.is_done() = " << task.is_done() << '\n';
    try {
      if (task.is_done()) {
        task.get();
        std::cerr << "Authenticated\n";
      }
    } catch (pplx::invalid_operation &e) {
      std::cerr << e.what() << '\n';
    }
  }

  void upload_file() {
    std::cerr << "UPLOAD ELEFANTE\n";
    web::http::client::http_client_config config;
    config.set_oauth2(m_oauth2_config);

    web::http::client::http_client client("https://www.googleapis.com", config);

    auto request = http_request(methods::POST);
    request.set_request_uri("/upload/drive/v3/files");

    std::vector<uint8_t> filedata;
    std::ifstream file{"/home/umberto/Downloads/elefante.jpeg",
                       std::ios::binary};
    file.unsetf(std::ios::skipws);
    file.seekg(0, std::ios::end);
    auto filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    filedata.insert(filedata.begin(), std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());

    auto &head = request.headers();
    head.set_content_type("application/octet-stream");
    head.set_content_length(filesize);
    head.add("uploadType", "media");
    request.set_body(filedata);

    client.request(request)
        .then([=](http_response response) {
          std::cerr << "response:\n" << response.extract_string().get() << '\n';
        })
        .wait();
  }
};

int main() {
  DriveSession drive("548501522105-nlu66mpp4eqihdhsad4e6gk0l0sqfbn7.apps."
                     "googleusercontent.com",
                     "onrSqOp1gpwr64nn6hu_vfCQ",
                     "https://accounts.google.com/o/oauth2/v2/auth",
                     "https://www.googleapis.com/oauth2/v4/token",
                     "http://localhost:8889/",
                     "https://www.googleapis.com/auth/drive");
  drive.run();
  drive.upload_file();
  return 0;
}
