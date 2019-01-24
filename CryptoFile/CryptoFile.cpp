#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Auth/GoogleDriveAuth.hpp"

#include <iostream>

int startup(std::string input_file) {
  std::cerr << "startup: input_file = " << input_file << '\n';
  auto drive = auth::GoogleDriveAuth();
  std::string cmd;
  std::getline(std::cin, cmd);

  return 0;
}
