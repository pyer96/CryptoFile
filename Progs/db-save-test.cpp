#include "CryptoFile/Db/Database.hpp"
#include "CryptoFile/Db/OriginalFile.hpp"

int main() {
  db::OriginalFile file;
  file.set_name("file_name");
  file.set_checksum("abcdefghi");
  file.save();
  return 0;
}
