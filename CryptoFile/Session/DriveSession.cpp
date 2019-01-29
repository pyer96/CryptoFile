#include "CryptoFile/Session/DriveSession.hpp"

#include <cpprest/http_client.h>

namespace session {
int DriveSession::upload_file(std::string file_path) {
  std::cerr << "upload_file\n";
  web::http::client::http_client client("https://www.googleapis.com",
                                        http_client_config());
  auto request = http_request(methods::POST);
  request.set_request_uri("/upload/drive/v3/files");

  std::vector<uint8_t> filedata;
  std::size_t filesize;
  try {
    std::ifstream file{file_path, std::ios::binary};
    file.unsetf(std::ios::skipws);
    file.seekg(0, std::ios::end);
    filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    filedata.insert(filedata.begin(), std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

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
  return 0;
}

} // namespace session
