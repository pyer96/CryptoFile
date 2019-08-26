#include "CryptoFile/Session/ServiceSession.hpp"

#include <boost/filesystem/path.hpp>

namespace cryptofile {
namespace session {

ServiceSession::ServiceSession(db::CloudService cloud_service_id,
                               std::string auth_endpoint,
                               std::string access_endpoint,
                               std::string client_id,
                               std::string client_secrets,
                               std::string redirect_uri, std::string scope)
    : m_service_authenticator{auth_endpoint,  access_endpoint, client_id,
                              client_secrets, redirect_uri,    scope},
      m_cloud_service_id{cloud_service_id} {
  m_http_client_config.set_oauth2(m_service_authenticator.oauth2_config());
}

web::json::value ServiceSession::upload_file(std::string file_path) {
  std::vector<uint8_t> file_data;
  try {
    std::ifstream file{file_path, std::ios::binary};
    file.unsetf(std::ios::skipws);
    file.seekg(0, std::ios::end);
    file_data.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    file_data.insert(file_data.begin(), std::istream_iterator<uint8_t>(file),
                     std::istream_iterator<uint8_t>());
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  auto path = boost::filesystem::path(file_path);

  return upload_file(std::move(file_data), path.filename().c_str());
}
} // namespace session
} // namespace cryptofile
