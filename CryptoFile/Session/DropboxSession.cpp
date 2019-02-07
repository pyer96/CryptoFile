#include "CryptoFile/Session/DropboxSession.hpp"

#include <cpprest/json.h>

namespace session {
web::json::value
DropboxSession::upload_file(std::vector<std::uint8_t> file_data,
                            std::string file_name) {
  web::json::value arguments = web::json::value::object();
  arguments["path"] = web::json::value::string('/' + file_name);
  arguments["mode"] = web::json::value::string("add");
  arguments["autorename"] = web::json::value::boolean(true);
  arguments["mute"] = web::json::value::boolean(false);
  arguments["strict_conflict"] = web::json::value::boolean(false);

  web::http::client::http_client upfile("https://content.dropboxapi.com",
                                        http_client_config());
  auto drive_file_request = http_request(methods::POST);
  drive_file_request.set_request_uri("/2/files/upload");
  auto &head = drive_file_request.headers();
  head.set_content_type("application/octet-stream");
  head.add("Dropbox-API-Arg", arguments.serialize());
  drive_file_request.set_body(file_data);
  std::cerr << "request for file ---->" << drive_file_request.to_string();

  web::json::value response_json;
  upfile.request(drive_file_request)
      .then([=, &response_json](http_response response) {
        auto task = response.extract_json();
        task.wait();
        response_json = task.get();
        std::cerr << "resp = \n{\n" << response_json.serialize() << "\n}\n";
      })
      .wait();

  return response_json;
}
std::vector<std::uint8_t>
DropboxSession::download_file(std::string cloud_file_id) {
  std::cerr << "cloud_file_id = " << cloud_file_id << '\n';
  web::json::value arguments = web::json::value::object();
  arguments["path"] = web::json::value::string(cloud_file_id);

  web::http::client::http_client downfile("https://content.dropboxapi.com",
                                          http_client_config());
  auto down_request = http_request(methods::POST);

  down_request.set_request_uri("/2/files/download");
  auto &header = down_request.headers();
  header.add("Dropbox-API-Arg", arguments.serialize());
  header.set_content_type("text/plain");

  std::vector<std::uint8_t> file;
  downfile.request(down_request)
      .then([=, &file](http_response response) {
        auto task = response.extract_vector();
        task.wait();
        file = task.get();
        std::cerr << "file.size() = " << file.size() << '\n';
      })
      .wait();

  return file;
}

} // namespace session
