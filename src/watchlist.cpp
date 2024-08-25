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
  stocks_.erase(symbol);
  saveWatchlist();
  cout << "Successfully removed " << symbol << " from the watchlist" << endl;
}

void Watchlist::fetchStockData(std::string& symbol)
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

void Watchlist::saveWatchlist()
{
  cout << "Saving watchlist at " << WATCHLIST_PATH << endl;
  ofstream outFile(WATCHLIST_PATH);
  if (!outFile) 
  {
    cerr << "Error saving watchlist: " << WATCHLIST_PATH << endl;
    return;
  }
  
  for (const auto& stock : stocks_) 
  {
    outFile << stock << endl;
  }

  outFile.close();
}

void Watchlist::loadWatchlist()
{
  if (!filesystem::exists(WATCHLIST_PATH))
  {
    cerr << "File does not exist at " << WATCHLIST_PATH << endl;
    return;
  }

  ifstream file(WATCHLIST_PATH);
  if (file.is_open())
  {
    string line;
    while (getline(file, line)) 
    {
      stocks_.push_back(line);
    }
    file.close();
  }
  else
  {
    cerr << "Failed to open file: " << WATCHLIST_PATH << endl;
  }
}

