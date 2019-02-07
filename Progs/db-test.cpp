#include "CryptoFile/Db/OriginalFile.hpp"
#include "CryptoFile/Db/Section.hpp"
#include <fmt/format.h>
#include <iostream>
#include <sqlite3.h>
#include <vector>

int main() {
  sqlite3 *db;
  sqlite3_stmt *stmt;
  std::vector<db::OriginalFile> m_original_files;
  std::vector<db::Section> m_sections;

  if (sqlite3_open_v2("Resources/crypto-file.db", &db,
                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr)) {
    std::cerr << "Error while opening database: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }
  {
    std::string query = "SELECT * FROM [original_file];";
    sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
    auto done = false;
    while (not done) {
      switch (sqlite3_step(stmt)) {
      case SQLITE_ROW: {
        m_original_files.emplace_back();
        auto &last = m_original_files.back();
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
    for (const auto &f : m_original_files) {
      std::cerr << fmt::format(
          "original_file_id = {}\nchecksum = {}\nname = {}\n\n", f.id(),
          f.checksum(), f.name());
    }
  }
  {
    std::string query = "SELECT * FROM [section];";
    sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
    auto done = false;
    while (not done) {
      switch (sqlite3_step(stmt)) {
      case SQLITE_ROW: {
        m_sections.emplace_back();
        auto &last = m_sections.back();
        last.set_id(sqlite3_column_int(stmt, 0));
        last.set_original_file_id(sqlite3_column_int(stmt, 1));
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
    for (const auto &s : m_sections) {
      std::cerr << fmt::format(
          "section_id = {}\noriginal_file_id = {}\nname = {}\norder = {}\n"
          "cloud_service_id = {}\nsection_cloud_id = {}\n\n",
          s.id(), s.original_file_id(), s.name(), s.order(),
          s.cloud_service_id(), s.section_cloud_id());
    }
  }
  sqlite3_close(db);
  std::cerr << "DATABASE CLOSED\n";
  return 0;
}
