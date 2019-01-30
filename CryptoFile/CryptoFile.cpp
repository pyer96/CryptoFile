#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Session/DriveSession.hpp"
#include "CryptoFile/Session/DropboxSession.hpp"

#include <iostream>

int startup(std::string input_file) {
  std::cerr << "startup: input_file = " << input_file << '\n';
  std::cerr << "\n***Google Drive Session***\n";
  session::DriveSession drive;
  drive.upload_file(input_file);
  std::cerr << "\n***Dropbox Session***\n";
  session::DropboxSession dropbox;
  dropbox.upload_file(input_file);
  return 0;
}
