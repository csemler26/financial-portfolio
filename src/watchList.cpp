#include "watchList.h"
#include "market.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>

using namespace std;

WatchList::WatchList()
{
  loadWatchList();
}

WatchList::~WatchList()
{
  saveWatchList();
}

void WatchList::addSymbol(std::string &symbol)
{
  stocks.push_back(symbol);
  saveWatchList();
  cout << "Successfully added " << symbol << " from the watchlist" << endl;
}

void WatchList::removeSymbol(std::string &symbol)
{
  stocks.erase(std::remove(stocks.begin(), stocks.end(), symbol), stocks.end());
  saveWatchList();
  cout << "Successfully removed " << symbol << " from the watchlist" << endl;
}

// void WatchList::fetchStockData()
void WatchList::fetchStockData(std::string& symbol)
{
  StockMarket market;
  Stock stock = market.fetchMarketData(symbol);

  lock_guard<mutex> guard(printMutex);
  cout << stock.symbol << " : $" << stock.price << endl;
}

void WatchList::printWatchList()
{
  std::vector<std::thread> threads;
  for (auto& stock : stocks) {
    threads.emplace_back([this, &stock]() {
      this->fetchStockData(stock);
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

void WatchList::saveWatchList()
{
  std::ofstream file(watchListPath);
  if (file.is_open()) {
    for (const auto& stock : stocks) {
        file << stock << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Unable to open file for saving watch list." << std::endl;
  }
}

void WatchList::loadWatchList()
{
  std::ifstream file(watchListPath);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      stocks.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file for loading watch list." << std::endl;
  }
}

