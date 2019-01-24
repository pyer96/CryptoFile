#include <iostream>
#include <regex>

#include "googleapis/client/util/status.h"

class GoogleDrive {
private:
  std::string m_email;

public:
  googleapis::util::Status startup();
  googleapis::util::Status get_email();
};

googleapis::util::Status GoogleDrive::startup() {
  // Set up HttpTransportLayer.
  googleapis::util::Status status;
  /*  config_.reset(new googleapis::client::HttpTransportLayerConfig);
    googleapis::client::HttpTransportFactory *factory =
        new googleapis::client::CurlHttpTransportFactory(config_.get());
    config_->ResetDefaultTransportFactory(factory);
    // We consider the 'roots.pem' to be in the build folder */
  return status;
}

googleapis::util::Status GoogleDrive::get_email() {
  googleapis::util::Status status;
  std::string email;
  std::cout << "Email: ";
  std::getline(std::cin, email);
  if (!email.empty()) {
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if (!std::regex_match(email, pattern)) {
      return googleapis::client::StatusInvalidArgument("Invalid email");
    }
    m_email = email;
    return googleapis::client::StatusOk();
  }
  return googleapis::client::StatusInvalidArgument("Email is empty");
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "GIVE ME THE SECRETS\n";
    return 1;
  }
  std::cout << "Welcome to Google Drive APIs test\n";
  GoogleDrive drive;
  auto status = drive.get_email();
  if (!status.ok()) {
    std::cerr << status.error_message() << '\n';
    return 1;
  }
  return 0;
}
