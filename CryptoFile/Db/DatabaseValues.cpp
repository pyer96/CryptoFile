#include "CryptoFile/Db/DatabaseValues.hpp"
#include "CryptoFile/Db/Database.hpp"

namespace cryptofile {
namespace db {
void get_original_files(
    std::vector<std::unique_ptr<OriginalFile>> &original_files) {
  auto db = Database::instance()->db();
  sqlite3_stmt *stmt;

  {
    std::string query = "SELECT * FROM [original_file];";
    sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
    auto done = false;
    while (not done) {
      switch (sqlite3_step(stmt)) {
      case SQLITE_ROW: {
        original_files.emplace_back(std::make_unique<OriginalFile>());
        auto &new_original_file = original_files.back();
        new_original_file->set_id(sqlite3_column_int(stmt, 0));
        new_original_file->set_checksum(
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        new_original_file->set_name(
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
    for (auto &original_file : original_files) {
      std::string query =
          "SELECT * FROM [section] where [original_file_id] = " +
          std::to_string(original_file->id()) + " ORDER BY [order] ASC;";
      sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
      auto done = false;
      while (not done) {
        switch (sqlite3_step(stmt)) {
        case SQLITE_ROW: {
          auto &sections = original_file->sections();
          sections.emplace_back(std::make_unique<Section>());
          auto &new_section = sections.back();
          new_section->set_id(sqlite3_column_int(stmt, 0));
          new_section->set_original_file_id(sqlite3_column_int(stmt, 1));
          new_section->set_name(
              reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
          new_section->set_order(sqlite3_column_int(stmt, 3));
          new_section->set_cloud_service_id(sqlite3_column_int(stmt, 4));
          new_section->set_section_cloud_id(
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
} // namespace db
/*
std::vector<std::unique_ptr<OriginalFile>> &get_original_file() {
  return s_original_files;
}
*/
} // namespace db
} // namespace cryptofile

