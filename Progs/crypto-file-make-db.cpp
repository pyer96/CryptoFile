#include <iostream>
#include <sqlite3.h>

int main() {
  sqlite3 *db;

  if (sqlite3_open_v2("Resources/crypto-file.db", &db,
                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr)) {
    std::cerr << "Error while opening database: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  std::string sql_stmt = "CREATE TABLE [original_file] ("
                         "[original_file_id]   INTEGER  PRIMARY KEY,"
                         "[checksum]           TEXT              NOT NULL,"
                         "[name]               TEXT              NOT_NULL);";
  if (sqlite3_exec(db, sql_stmt.c_str(), nullptr, 0, nullptr) != SQLITE_OK) {
    std::cerr << "Error while creating table: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  sql_stmt.clear();
  sql_stmt = "CREATE TABLE [cloud_service] ("
             "[cloud_service_id]   INTEGER  PRIMARY KEY,"
             "[name]               TEXT              NOT NULL);";
  if (sqlite3_exec(db, sql_stmt.c_str(), nullptr, 0, nullptr) != SQLITE_OK) {
    std::cerr << "Error while creating table: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  sql_stmt.clear();
  sql_stmt = "CREATE TABLE [section] ("
             "[section_id]         INTEGER  PRIMARY KEY,"
             "[original_file_id]   INTEGER           NOT NULL,"
             "[name]               TEXT              NOT NULL,"
             "[order]              INT               NOT NULL,"
             "[cloud_service_id]   INTEGER           NOT NULL,"
             "[section_cloud_id]   TEXT              NOT NULL,"
             "FOREIGN KEY ([original_file_id]) REFERENCES "
             "original_file([original_file_id]),"
             "FOREIGN KEY ([cloud_service_id]) REFERENCES "
             "cloud_service([cloud_service_id]));";
  if (sqlite3_exec(db, sql_stmt.c_str(), nullptr, 0, nullptr) != SQLITE_OK) {
    std::cerr << "Error while creating table: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  sql_stmt.clear();
  sql_stmt = "INSERT INTO cloud_service([name]) VALUES "
             "('Drive'),('Dropbox');";
  if (sqlite3_exec(db, sql_stmt.c_str(), nullptr, 0, nullptr) != SQLITE_OK) {
    std::cerr << "Error while populating table: " << sqlite3_errmsg(db) << '\n';
    return 1;
  }
  sqlite3_close(db);
  return 0;
}
