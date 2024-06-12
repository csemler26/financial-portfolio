#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <string>
#include <vector>
#include <mutex>
#include <filesystem>
#include <unordered_map>
#include <curl/curl.h>
#include "json.h"
#include "dataTypes.h"
#include "market.h"

const std::filesystem::path watchlistPath = "/var/financial-portfolio/watchlist.txt";

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
  void fetchStockData(std::string& symbol);

  std::vector<std::string> stocks_;
  std::mutex printMutex_;
};

#endif // WATCHLIST_H