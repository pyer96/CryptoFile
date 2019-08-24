
#include "CryptoFile/Db/DatabaseValues.hpp"

#include <iostream>

using namespace cryptofile;

int main() {
  db::init_database();
  auto &original_files = db::get_original_file();
  std::cerr << "s_original_files.size() = " << original_files.size() << '\n';
  for (const auto &original_file : original_files) {
    original_file->print_members();
    std::cerr << '\n';
    for (const auto &section : original_file->sections()) {
      section->print_members();
    }
    std::cerr << "\n\n";
  }
  original_files.emplace_back(std::make_unique<cryptofile::db::OriginalFile>());
  original_files.back()->set_name("AAAAAAA");
  original_files.back()->set_checksum("BBBBBBB");
  auto &sec = original_files.back()->sections();
  sec.emplace_back(std::make_unique<cryptofile::db::Section>());
  sec.back()->set_name("AAAAA");
  sec.back()->set_order(1);
  sec.back()->set_cloud_service_id(1);
  sec.back()->set_section_cloud_id("BBBBBBB");
  original_files.back()->save();
  auto &of = db::get_original_file();
  of.back()->print_members();
  return 0;
}

