#include "CryptoFile/Session/DriveSession.hpp"

#include <cpprest/http_client.h>

namespace cryptofile {
namespace session {
web::json::value DriveSession::upload_file(std::vector<std::uint8_t> file_data,
                                           std::string file_name) {
  std::cerr << "upload_file\n";
  web::http::client::http_client client("https://www.googleapis.com",
                                        http_client_config());
  auto request = http_request(methods::POST);
  request.set_request_uri("/upload/drive/v3/files");

  auto &head = request.headers();
  head.set_content_type("application/octet-stream");
  head.set_content_length(file_data.size());
  head.add("uploadType", "media");
  head.add("name", file_name);
  request.set_body(file_data);

  web::json::value response_json;
  client.request(request)
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
DriveSession::download_file(std::string cloud_file_id) {
  web::http::client::http_client downfile("https://www.googleapis.com",
                                          http_client_config());
  std::cerr << "cloud_file_id = " << cloud_file_id << '\n';
  auto down_request = http_request(methods::GET);
  auto uri = uri_builder("/drive/v3/files/");
  uri.append_path(cloud_file_id);
  uri.append_query("alt", "media");
  down_request.set_request_uri(uri.to_uri());
  // down_request.headers().set_content_type("text/plain");
  // down_request.headers().add("Accept", "application/octet-stream");

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
} // namespace cryptofile
