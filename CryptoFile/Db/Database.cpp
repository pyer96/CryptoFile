#include "CryptoFile/Db/Database.hpp"
#include <sqlite3.h>

namespace db {
Database *Database::s_instance = nullptr;
} // namespace db
