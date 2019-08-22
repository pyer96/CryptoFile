#ifndef __CryptoFile__Db__Database__
#define __CryptoFile__Db__Database__

#include <iostream>
#include <sqlite3.h>

namespace cryptofile {
namespace db {
class Database {
private:
  sqlite3 *m_db;
  Database() {
    if (sqlite3_open("Resources/crypto-file.db", &m_db)) {
      std::cerr << "Error while opening database: " << sqlite3_errmsg(m_db)
                << '\n';
    }
  }
  ~Database() { sqlite3_close(m_db); }

public:
  static Database *s_instance;
  static Database *instance() {
    if (not s_instance) {
      s_instance = new Database;
    }
    return s_instance;
  }
  auto db() { return m_db; }
};
} // namespace db
} // namespace cryptofile
#endif

