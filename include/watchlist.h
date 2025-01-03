#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <string>
#include <mutex>
#include <filesystem>
#include <curl/curl.h>
#include "json.h"
#include "dataTypes.h"
#include "market.h"

const std::filesystem::path WATCHLIST_PATH = "/var/financial-portfolio/watchlist.txt";

class Watchlist {
public:
  Watchlist();
  ~Watchlist();
  void addSymbol(std::string& symbol);
  void removeSymbol(std::string& symbol);
  void printWatchList();

private:
  void saveWatchlist();
  void loadWatchlist();
  void fetchStockData(const std::string& symbol);

  UnorderedSet<std::string> stocks_;
  std::mutex printMutex_;
};

#endif // WATCHLIST_H