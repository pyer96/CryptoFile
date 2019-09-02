#include "CryptoFile/Aont/Section.hpp"

#include "CryptoFile/CryptoFile.hpp"
#include "CryptoFile/Db/Database.hpp"
#include "CryptoFile/Db/OriginalFile.hpp"
#include "CryptoFile/Db/Section.hpp"
#include "CryptoFile/Session/DriveSession.hpp"
#include "CryptoFile/Session/DropboxSession.hpp"

#include <boost/filesystem/path.hpp>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <sqlite3.h>

void list(const std::vector<cryptofile::db::OriginalFile> &original_files) {
  std::cout << '\n';
  for (std::size_t i = 0; i < original_files.size(); ++i) {
    std::cout << fmt::format("({}) {}\n", i, original_files[i].name());
  }
  std::cout << '\n';
}
void read_db(std::vector<cryptofile::db::OriginalFile> &original_files,
             std::vector<cryptofile::db::Section> &sections) {
  original_files.clear();
  sections.clear();
  sqlite3_stmt *stmt;
  auto db = cryptofile::db::Database::instance()->db();
  {
    std::string query = "SELECT * FROM [original_file];";
    sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
    auto done = false;
    while (not done) {
      switch (sqlite3_step(stmt)) {
      case SQLITE_ROW: {
        original_files.emplace_back();
        auto &last = original_files.back();
        last.set_id(sqlite3_column_int(stmt, 0));
        last.set_checksum(
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        last.set_name(
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
      } break;
      case SQLITE_DONE:
        done = true;
        break;
      default:
        std::cerr << "Error: " << sqlite3_errmsg(db) << '\n';
      }
    }
  }
  {
    std::string query = "SELECT * FROM [section];";
    sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
    auto done = false;
    while (not done) {
      switch (sqlite3_step(stmt)) {
      case SQLITE_ROW: {
        sections.emplace_back();
        auto &last = sections.back();
        last.set_id(sqlite3_column_int(stmt, 0));
        last.set_original_file_id(sqlite3_column_int(stmt, 1));
std::vector<std::unique_ptr<aont::Section>>
aont_mask(std::vector<std::uint8_t> &data, std::size_t sections_number,
          callback_t callback) {
  std::vector<std::unique_ptr<aont::Section>> sections;
  sections.reserve(sections_number);
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(
      CryptoPP::AES::MAX_KEYLENGTH);           // 32 bytes (256 bits)
  CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; // 16 bytes (128 bits)
  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(iv, sizeof(iv));

  double standard_section_size =
      static_cast<float>(data.size()) / static_cast<float>(sections_number);
  auto normal_section_size = std::ceil(standard_section_size);
  auto last_section_size =
      normal_section_size -
      ((normal_section_size * sections_number) - data.size());

  for (std::size_t i = 0; i < sections_number; ++i) {
    auto section_size =
        i < sections_number - 1 ? normal_section_size : last_section_size;
    auto section_data = gsl::span<std::uint8_t>(
        &(data.data()[static_cast<std::size_t>(normal_section_size) * i]),
        section_size);

    sections.emplace_back(
        std::make_unique<aont::EncryptSection>(std::move(section_data), key));
  }
  auto encrypted_key = std::vector<std::uint8_t>(&(key.BytePtr()[0]),
                                                 &(key.BytePtr()[key.size()]));
  for (const auto &sec : sections) {
    auto hash = std::vector<std::uint8_t>(
        reinterpret_cast<aont::EncryptSection *>(sec.get())->get_hash());
    CryptoPP::xorbuf(encrypted_key.data(), encrypted_key.data(), hash.data(),
                     hash.size());
  }
  sections.emplace_back(std::make_unique<aont::LastSection>(encrypted_key));

  callback(sections);
  return sections;
}
        last.set_name(
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        last.set_order(sqlite3_column_int(stmt, 3));
        last.set_cloud_service_id(sqlite3_column_int(stmt, 4));
        last.set_section_cloud_id(
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
      } break;
      case SQLITE_DONE:
        done = true;
        break;
      default:
        std::cerr << "Error: " << sqlite3_errmsg(db) << '\n';
      }
    }
  }
}

void upload(cryptofile::session::DriveSession &drive, cryptofile::session::DropboxSession &dropbox,
            std::vector<cryptofile::db::OriginalFile> &original_files,
            std::vector<cryptofile::db::Section> &sections) {
  std::string file_path;
  std::cout << "Enter file path: ";
  std::cin.ignore();
  std::getline(std::cin, file_path);
  std::vector<uint8_t> data;
  std::ifstream file{file_path, std::ios::binary};
  if (not file.is_open()) {
    std::cerr << "File not found\n";
    return;
  }

  file.unsetf(std::ios::skipws);
  file.seekg(0, std::ios::end);
  auto filesize = file.tellg();
  file.seekg(0, std::ios::beg);
  std::cout << "initial file size = " << filesize << '\n';
  data.reserve(filesize);
  data.insert(data.begin(), std::istream_iterator<uint8_t>(file),
              std::istream_iterator<uint8_t>());

  int section_number = 2;

  double standard_section_size =
      static_cast<float>(data.size()) / static_cast<float>(section_number);
  auto normal_section_size = std::ceil(standard_section_size);
  auto file_name =
      std::string(boost::filesystem::path(file_path).filename().c_str());
  /* auto &last =*/original_files.emplace_back();
  auto &last = original_files.back();
  last.set_checksum("");
  last.set_name(file_name);
  last.save();
  std::cerr << "name = " << last.name() << " id = " << last.id() << '\n';

  {
    std::vector<std::uint8_t> section;
    auto section_name = file_name + "_1";
    section.insert(section.begin(), data.begin(),
                   data.begin() + normal_section_size);
    auto response = drive.upload_file(section, section_name);
    auto last_section = sections.emplace_back();
    last_section.set_name(section_name);
    last_section.set_order(1);
    last_section.set_original_file_id(last.id());
    last_section.set_cloud_service_id(1);
    last_section.set_section_cloud_id(response["id"].as_string());
    last_section.save();
  }
  {
    std::vector<std::uint8_t> section;
    auto section_name = file_name + "_2";
    section.insert(section.begin(), data.begin() + normal_section_size,
                   data.end());
    auto response = dropbox.upload_file(section, section_name);
    auto last_section = sections.emplace_back();
    last_section.set_name(section_name);
    last_section.set_order(2);
    last_section.set_original_file_id(last.id());
    last_section.set_cloud_service_id(2);
    last_section.set_section_cloud_id(response["id"].as_string());
    last_section.save();
  }
}

void download(cryptofile::session::DriveSession &drive, cryptofile::session::DropboxSession &dropbox,
              std::vector<cryptofile::db::OriginalFile> &original_files,
              std::vector<cryptofile::db::Section> &sections) {
  read_db(original_files, sections);
  std::cout << "Select the file to download: ";
  list(original_files);
  std::vector<std::uint8_t> file;
  std::cin.ignore();
  std::string file_index;
  std::getline(std::cin, file_index);
  auto index = std::atoi(file_index.c_str());
  std::vector<std::uint8_t> section_1;
  std::vector<std::uint8_t> section_2;
  {
    for (const auto &s : sections) {
      std::cerr << s.original_file_id() << " == " << original_files[index].id()
                << '\n';
      if (s.original_file_id() == original_files[index].id()) {
        std::cerr << "s.cloud_service_id() = " << s.cloud_service_id() << '\n';
        if (s.cloud_service_id() == 1) {
          section_1 = drive.download_file(s.section_cloud_id());
        } else if (s.cloud_service_id() == 2) {
          section_2 = dropbox.download_file(s.section_cloud_id());
        }
      }
    }
    std::cerr << "section_1.size() = " << section_1.size()
              << " section_2.size() = " << section_2.size() << '\n';
    if (not section_1.empty() and not section_2.empty()) {
      file.insert(file.begin(), section_1.begin(), section_1.end());
      file.insert(file.end(), section_2.begin(), section_2.end());
      std::ofstream os;
      os.open(original_files[index].name(),
              std::ofstream::out | std::fstream::binary);
      os.write(reinterpret_cast<const char *>(file.data()), file.size());
    }
  }
}


int main() {

  std::ifstream file("Resources/CryptoFile/crypto_file_banner");
  std::cout << file.rdbuf() << '\n';
  std::cout << "AUTHENTICATION WITH ONLINE CLOUDS" << '\n';

  session::DriveSession drive;
  session::DropboxSession dropbox;

  std::vector<db::OriginalFile> original_files;
  std::vector<db::Section> sections;
  read_db(original_files, sections);

  bool exit = false;

  while (!exit) {
    std::cout << "Choose one of the following\n"
                 "1.  LIST\n"
                 "2.  UPLOAD\n"
                 "3.  DOWNLOAD\n"
                 "4.  EXIT\n";
    char choice;
    std::cin >> choice;
    switch (choice) {

    case '1':
      list(original_files);
      break;

    case '2':
      upload(drive, dropbox, original_files, sections);
      break;

    case '3':
      download(drive, dropbox, original_files, sections);
      break;

    case '4':
      exit = true;
      break;
    }
  } // while
  return 0;
}

