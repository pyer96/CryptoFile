#include "CryptoFile/CryptoFileSession.hpp"

int main() {
  {
    std::vector<cryptofile::db::CloudService> selected_clouds = {
        cryptofile::db::CloudService::Drive,
        cryptofile::db::CloudService::Dropbox};
    cryptofile::CryptoFileSession session{selected_clouds};
    session.save_file_on_clouds(5, "/home/pier/Desktop/condorello",
                                selected_clouds);
  }
  return 0;
}
