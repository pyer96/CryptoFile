#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Session/DriveSession.hpp"

#include <iostream>

int startup(std::string input_file) {
  std::cerr << "startup: input_file = " << input_file << '\n';
  session::DriveSession drive;
  drive.upload_file(input_file);
  return 0;
}
