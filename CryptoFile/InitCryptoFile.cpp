#include "CryptoFile/InitCryptoFile.hpp"

#include "CryptoFile/CryptoFileSession.hpp"
#include "CryptoFile/Db/CloudService.hpp"
//#include "CryptoFile/ErrLog/ErrLog.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>

namespace cryptofile {

void upload(CryptoFileSession &session) {
  std::size_t section_number;
  boost::filesystem::path file_path;
  std::vector<db::CloudService> selected_clouds;

  std::cout << "Tell CryptoFile the file path and the number of section to "
               "split it into...\n"
            << "File Path           :";
  std::cin >> file_path; //?
 // ErrLog::instance().add(file_path.c_str(), true);
  
  std::cout << "\nSection number    :";
  std::cin >> section_number;
  char answer;
  std::cout << "\nUse Drive? [y/n]  :";
  std::cin >> answer;
  if (answer == 'y') {
    selected_clouds.emplace_back(db::CloudService::Drive);
  }
  std::cout << "\nUse Dropbox? [y/n]:";
  std::cin >> answer;
  if (answer == 'y') {
    selected_clouds.emplace_back(db::CloudService::Dropbox);
  }
  session.save_file_on_clouds(section_number, file_path, selected_clouds);
}
void download(CryptoFileSession &session)
{
  std::cout<<"\nSelect which file you wish to restore!\n";
  session.list_original_files();
  std::size_t choice;
  std::cin >> choice;
 session.restore_file_from_clouds(choice); 
}
void init_cryptofile() {
  std::ifstream banner("Resources/CryptoFile/crypto_file_banner");
  std::cout << "\e[32m\e[5m" << banner.rdbuf() << "\e[25m\e[39m" << std::endl;
  std::cout << "AUTHENTICATE YOURSELF WITH ONLINE CLOUDS\n\n";

  std::vector<db::CloudService> clouds_to_authenticate;

  bool condition = true;
  while (condition) {
    std::cout << "\n\nChoose between available clouds:\n"
              << "1. Google Drive\n"
              << "2. Dropbox\n"
              << "3. Ok, im done. Enough authentication for me!\n";
    char auth_choice;
    std::cin >> auth_choice;
    switch (auth_choice) {
    case '1':
      clouds_to_authenticate.emplace_back(db::CloudService::Drive);
      break;
    case '2':
      clouds_to_authenticate.emplace_back(db::CloudService::Dropbox);
      break;
    case '3':
      condition = false;
      break;
    }
  }
  CryptoFileSession Session(clouds_to_authenticate);

  bool loop = true;
  while (loop) {
    std::cout << "\n\nChoose one of the following\n"
                 "1.  List previously uploaded files \n"
                 "2.  Upload a new file\n"
                 "3.  Download and restore an existing file\n"
                 "4.  Quit CryptoFile\n\n";
    char choice;
    std::cin >> choice;
    switch (choice) {

    case '1':
      Session.list_original_files();
      break;

    case '2':
      upload(Session);
      break;

    case '3':
       download(Session);
      break;

    case '4':
      loop = false;
      break;
    } // while
  }
}
} // namespace cryptofile
