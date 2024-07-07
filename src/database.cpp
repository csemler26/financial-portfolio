#include "database.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database::Database(const std::string& dbFile) 
{
  if (sqlite3_open(dbFile.c_str(), &db_) != SQLITE_OK) 
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db_) << std::endl;
  }
}

Database::~Database() 
{
  sqlite3_close(db_);
}

bool Database::executeScript(const std::string& scriptFilePath) 
{
  std::ifstream file(scriptFilePath);
  if (!file.is_open()) 
  {
    std::cerr << "Could not open file: " << scriptFilePath << std::endl;
    return false;
  }

  std::stringstream ss;
  ss << file.rdbuf();
  std::string sql = ss.str();
  char* errorMsg = nullptr;
  int result = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errorMsg);

  if (result != SQLITE_OK) 
  {
    std::cerr << "SQL error: " << errorMsg << std::endl;
    sqlite3_free(errorMsg);
    return false;
  }
  return true;
}