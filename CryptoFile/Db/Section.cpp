#include "CryptoFile/Db/Section.hpp"
#include "CryptoFile/Db/Database.hpp"

#include <fmt/format.h>
#include <sqlite3.h>

namespace db {
void Section::save() {
  sqlite3_stmt *stmt;
  auto query_str =
      fmt::format("INSERT INTO section([original_file_id], [name], [order], "
                  "[cloud_service_id], [section_cloud_id]) "
                  "VALUES ({}, '{}', {}, {}, '{}');",
                  m_original_file_id, m_name, m_order, m_cloud_service_id,
                  m_section_cloud_id);
  auto db = Database::instance()->db();
  sqlite3_prepare(db, query_str.c_str(), query_str.size(), &stmt, nullptr);
  if (sqlite3_step(stmt) == SQLITE_DONE) {
    m_section_id = sqlite3_last_insert_rowid(db);
    std::cerr << "last_rowid = " << m_original_file_id << '\n';
  } else {
    std::cerr << fmt::format("Error: {}", sqlite3_errmsg(db));
  }
  sqlite3_finalize(stmt);
}

void Section::print_members() {
  std::cerr << fmt::format(
      "section_id = {}\noriginal_file_id = {}\nname = {}\norder = {}\n"
      "cloud_service_id = {}\nsection_cloud_id = {}\n",
      m_section_id, m_original_file_id, m_name, m_order, m_cloud_service_id,
      m_section_cloud_id);
}
} // namespace db
