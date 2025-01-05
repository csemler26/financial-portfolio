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

sqlite3_stmt* Database::prepareStatement(const std::string& query) {
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
  {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
    return nullptr;
  }
  return stmt;
}

void Database::loadWatchlist(UnorderedSet<std::string>& watchlist) 
{
  std::string sql = "SELECT stock_name FROM watchlist_stocks;";
  sqlite3_stmt* stmt = prepareStatement(sql);
  if (stmt) 
  {
    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
      std::string stockName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
      watchlist.insert(stockName);
    }
    sqlite3_finalize(stmt);
  }
}

void Database::addStockToWatchlist(const std::string& stockName) 
{
  std::string sql = "INSERT INTO watchlist_stocks (stock_name) VALUES (?);";
  sqlite3_stmt* stmt = prepareStatement(sql);
  if (stmt) 
  {
    sqlite3_bind_text(stmt, 1, stockName.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
}

void Database::removeStockFromWatchlist(const std::string& stockName) 
{
  std::string sql = "DELETE FROM watchlist_stocks WHERE stock_name = ?;";
  sqlite3_stmt* stmt = prepareStatement(sql);
  if (stmt) 
  {
    sqlite3_bind_text(stmt, 1, stockName.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
}