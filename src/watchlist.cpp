#include "watchlist.h"
#include "market.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>

using namespace std;

Watchlist::Watchlist(Database& db) : db_(db)
{
  loadWatchlist();
}

Watchlist::~Watchlist()
{
}

void Watchlist::addSymbol(std::string &symbol)
{
  // skip if duplicate
  if (stocks_.find(symbol) != stocks_.end())
  {
    cout << "Symbol already exists in the watchlist" << endl;
    return;
  }

  stocks_.insert(symbol);
  db_.addStockToWatchlist(symbol);
}

void Watchlist::removeSymbol(std::string &symbol)
{
  stocks_.erase(symbol);  
  db_.removeStockFromWatchlist(symbol);
}

void Watchlist::fetchStockData(const std::string& symbol)
{
  StockMarket market;
  Stock stock = market.fetchMarketData(symbol);

  lock_guard<mutex> guard(printMutex_);
  cout << stock.symbol
            << fixed << setprecision(2) 
            << " : $" << stock.price << endl;
}

void Watchlist::printWatchList()
{
  vector<thread> threads;
  for (auto& stock : stocks_) 
  {
    threads.emplace_back([this, &stock]() 
    {
      this->fetchStockData(stock);
    });
  }

  for (auto& thread : threads) 
  {
    thread.join();
  }
}

void Watchlist::loadWatchlist()
{
  cout << "Loading watchlist from SQL database" << endl;
  db_.loadWatchlist(stocks_);
  cout << "Done loading watchlist from SQL database" << endl;
}

