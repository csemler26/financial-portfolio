#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "dataTypes.h"

class Database {
public:
  Database(const std::string& dbFile);
  ~Database();
  bool executeScript(const std::string& scriptFilePath);
  sqlite3_stmt* prepareStatement(const std::string& query);

  void loadWatchlist(UnorderedSet<std::string>& watchlist);
  void addStockToWatchlist(const std::string& stockName);
  void removeStockFromWatchlist(const std::string& stockName);

private:
  sqlite3* db_;
};

#endif // DATABASE_H