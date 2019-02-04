#include <fmt/format.h>
#include <iostream>
#include <sqlite3.h>
#include <vector>

class OriginalFile {
private:
  int m_id;
  std::string m_checksum;
  std::string m_name;
//  std::vector<Section*> m_sections;

public:
  OriginalFile(int id, std::string checksum, std::string name)
      : m_id{id}, m_checksum{checksum}, m_name{name} {}
  auto id() const { return m_id; }
  const auto &checksum() const { return m_checksum; }
  const auto &name() const { return m_name; }
  void save();
};

void OriginalFile::save() {
  auto stmt = fmt::format(
      "INSERT INTO original_file([checksum], [name]) VALUES ('{}', '{}');",
      m_checksum, m_name);
}

int main() {
  sqlite3 *db;
  sqlite3_stmt *stmt;
  std::vector<OriginalFile> m_original_files;

  if (sqlite3_open_v2("Resources/crypto-file.db", &db,
                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr)) {
    std::cerr << "Error while opening database: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }
  std::string query = "SELECT * FROM [original_file];";
  sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
  auto done = false;
  while (not done) {
    switch (sqlite3_step(stmt)) {
    case SQLITE_ROW:
      std::cerr << sqlite3_column_bytes(stmt, 0) << " "
                << sqlite3_column_int(stmt, 0) << ' '
                << sqlite3_column_text(stmt, 1) << ' '
                << sqlite3_column_text(stmt, 2) << '\n';
      m_original_files.emplace_back(
          sqlite3_column_int(stmt, 0),
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
          reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
      break;
    case SQLITE_DONE:
      done = true;
      break;
    default:
      std::cerr << "Error: " << sqlite3_errmsg(db) << '\n';
    }
  }
  sqlite3_close(db);
  std::cerr << "DATABASE CLOSED\n";
  for (const auto &f : m_original_files) {
    std::cerr << f.id() << '\n' << f.checksum() << '\n' << f.name() << "\n\n";
  }
  return 0;
}
