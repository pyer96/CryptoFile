#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Session/DriveSession.hpp"
#include "CryptoFile/Session/DropboxSession.hpp"

#include <iostream>

int startup(std::string input_file) {
  std::cerr << "startup: input_file = " << input_file << '\n';
  std::cerr << "\n***Google Drive Session***\n";
  session::DriveSession drive;
  auto response = drive.session::ServiceSession::upload_file(input_file);
  auto data = drive.download_file(response["id"].as_string());
  std::cerr << "data.size() = " << data.size() << '\n';
  std::ofstream os;
  os.open("/tmp/drive.html", std::ofstream::out | std::fstream::binary);
  os.write(reinterpret_cast<const char *>(data.data()), data.size());
  /* std::cerr << "\n***Dropbox Session***\n";
   session::DropboxSession dropbox;
   auto response = dropbox.session::ServiceSession::upload_file(input_file);
   auto data = dropbox.download_file(response["id"].as_string());
   std::cerr << "data.size() = " << data.size() << '\n';
   */
  ;
  return 0;
}
