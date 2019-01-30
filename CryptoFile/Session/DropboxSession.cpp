#include "CryptoFile/Session/DropboxSession.hpp"

namespace session {
int DropboxSession::upload_file(std::string file_path) {
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

  web::json::value arguments = web::json::value::object();
  arguments["path"] = web::json::value::string("/elefante.jpg");
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
  drive_file_request.set_body(filedata);
  std::cerr << "request for file ---->" << drive_file_request.to_string();

  upfile.request(drive_file_request)
      .then([=](http_response response) {
        std::cerr << "json file list ---->>>" << response.extract_string().get()
                  << '\n';
      })
      .wait();
  return 0;
}
} // namespace session
