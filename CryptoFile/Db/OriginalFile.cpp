#include "CryptoFile/Db/OriginalFile.hpp"
#include "CryptoFile/Db/Database.hpp"

#include <fmt/format.h>
#include <iostream>

namespace cryptofile {
namespace db {

void OriginalFile::save() {
  sqlite3_stmt *stmt;
  auto query_str = fmt::format("INSERT INTO original_file([checksum], "
                               "[name]) VALUES ('{}', '{}');",
                               m_checksum, m_name);
  auto db = Database::instance()->db();
  sqlite3_prepare(db, query_str.c_str(), query_str.size(), &stmt, nullptr);
  if (sqlite3_step(stmt) == SQLITE_DONE) {
    m_original_file_id = sqlite3_last_insert_rowid(db);
    std::cerr << "last_rowid = " << m_original_file_id << '\n';
  } else {
    std::cerr << fmt::format("Error: {}", sqlite3_errmsg(db));
  }
  sqlite3_finalize(stmt);
}
void OriginalFile::print_members() {
  std::cerr << fmt::format("original_file_id = {}\nchecksum = {}\nname = {}\n",
                           m_original_file_id, m_checksum, m_name);
}
} // namespace db
} // namespace cryptofile
