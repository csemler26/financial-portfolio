#include "database.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database::Database(const std::string& db_file) {
  if (sqlite3_open(db_file.c_str(), &db_) != SQLITE_OK) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db_) << std::endl;
  }
}

Database::~Database() {
  sqlite3_close(db_);
}

bool Database::executeScript(const std::string& script_file) {
  std::ifstream file(script_file);
  if (!file.is_open()) {
    std::cerr << "Could not open file: " << script_file << std::endl;
    return false;
  }

  std::stringstream ss;
  ss << file.rdbuf();
  std::string sql = ss.str();
  char* zErrMsg = nullptr;
  int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &zErrMsg);

  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
    return false;
  }
  return true;
}