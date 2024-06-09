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

const std::filesystem::path watchListPath = "/var/financial-portfolio/watchList.txt";

class WatchList {
public:
  WatchList();
  ~WatchList();
  void addSymbol(std::string& symbol);
  void removeSymbol(std::string& symbol);
  void printWatchList();

private:
  void saveWatchList();
  void loadWatchList();
  void fetchStockData(std::string& symbol);

  std::vector<std::string> stocks;
  std::mutex printMutex;
};

#endif // WATCHLIST_H