#include "CryptoFile/Db/Database.hpp"
#include <sqlite3.h>

namespace cryptofile {
namespace db {
Database *Database::s_instance = nullptr;
} // namespace db
} // namespace cryptofile
