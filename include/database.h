#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
  Database(const std::string& db_file);
  ~Database();
  bool executeScript(const std::string& script_file);
private:
  sqlite3* db_;
};

#endif // DATABASE_H