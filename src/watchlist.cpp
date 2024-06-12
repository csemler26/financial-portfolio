#include "watchlist.h"
#include "market.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>

using namespace std;

Watchlist::Watchlist()
{
  loadWatchlist();
}

Watchlist::~Watchlist()
{
  saveWatchlist();
}

void Watchlist::addSymbol(std::string &symbol)
{
  stocks_.push_back(symbol);
  saveWatchlist();
  cout << "Successfully added " << symbol << " from the watchlist" << endl;
}

void Watchlist::removeSymbol(std::string &symbol)
{
  stocks_.erase(std::remove(stocks_.begin(), stocks_.end(), symbol), stocks_.end());
  saveWatchlist();
  cout << "Successfully removed " << symbol << " from the watchlist" << endl;
}

void Watchlist::fetchStockData(std::string& symbol)
{
  StockMarket market;
  Stock stock = market.fetchMarketData(symbol);

  lock_guard<mutex> guard(printMutex_);
  cout << stock.symbol << " : $" << stock.price << endl;
}

void Watchlist::printWatchList()
{
  std::vector<std::thread> threads;
  for (auto& stock : stocks_) {
    threads.emplace_back([this, &stock]() {
      this->fetchStockData(stock);
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

void Watchlist::saveWatchlist()
{
  std::ofstream file(watchlistPath);
  if (file.is_open()) {
    for (const auto& stock : stocks_) {
        file << stock << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Unable to open file for saving watch list." << std::endl;
  }
}

void Watchlist::loadWatchlist()
{
  std::ifstream file(watchlistPath);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      stocks_.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file for loading watch list." << std::endl;
  }
}

