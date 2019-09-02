#include "CryptoFile/Db/Database.hpp"
#include "CryptoFile/Db/OriginalFile.hpp"
#include "CryptoFile/Db/Section.hpp"

int main() {
  db::OriginalFile file;
  file.set_name("file_name");
  file.set_checksum("abcdefghi");
  file.save();

  db::Section s1;
  s1.set_original_file_id(file.id());
  s1.set_name("section_1");
  s1.set_order(1);
  s1.set_cloud_service_id(1); // Google Drive
  s1.set_section_cloud_id("");
  s1.save();

  db::Section s2;
  s2.set_original_file_id(file.id());
  s2.set_name("section_2");
  s2.set_order(2);
  s2.set_cloud_service_id(2); // Dropbox
  s2.set_section_cloud_id("");
  s2.save();
  return 0;
}
