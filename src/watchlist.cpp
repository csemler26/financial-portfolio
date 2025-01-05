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

void Watchlist::addSymbol(const std::string &symbol)
{
  if (stocks_.find(symbol) != stocks_.end())
  {
    cout << "Symbol already exists in the watchlist" << endl;
    return;
  }
  
  stocks_[symbol] = Stock{symbol, 0.0};
  db_.addStockToWatchlist(symbol);
}

void Watchlist::removeSymbol(const std::string &symbol)
{
  stocks_.erase(symbol);  
  db_.removeStockFromWatchlist(symbol);
}

Stock Watchlist::fetchStockData(const std::string& symbol)
{
  StockMarket market;
  return market.fetchMarketData(symbol);
}

void Watchlist::updateStockPrices()
{
  vector<thread> threads;
  vector<Stock> fetchedStocks;
  mutex dataMutex;

  // Create threads to fetch stock data
  for (auto& [symbol, stock] : stocks_) 
  {
    threads.emplace_back([this, &dataMutex, &stock, &symbol]() 
    {
      Stock updatedStock = this->fetchStockData(symbol);
      
      // Store the fetched stock data in a thread-safe manner
      lock_guard<mutex> guard(dataMutex);
      stock = updatedStock;
    });
  }

  // Join all threads
  for (auto& thread : threads) 
  {
    thread.join();
  }

  updateSqlTableValues();
}
  
void Watchlist::printWatchList()
{
  lock_guard<mutex> guard(printMutex_);
  for (const auto& [symbol, stock] : stocks_) 
  {
    cout << stock.symbol
         << fixed << setprecision(2)
         << " : $" << stock.price << endl;
  }
}

// TODO: update this function
// Is it needed? - add method headers to existing functions to clarify their purpose
void Watchlist::updateSqlTableValues()
{
  for (const auto& [symbol, stock] : stocks_) 
  {
    db_.insertOrUpdateStockPrice(stock.symbol, stock.price);
  }
}

void Watchlist::loadWatchlist()
{
  db_.loadWatchlist(stocks_);
}

