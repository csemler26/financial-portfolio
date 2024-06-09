#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <curl/curl.h>
#include "include/json.h"
#include "include/market.h"
#include "include/portfolio.h"
#include "include/dataTypes.h"
#include "include/watchList.h"

using namespace std;

void init(Portfolio& portfolio)
{
  portfolio.loadPortfolio();
  portfolio.printPortfolio();
}

int main()
{
  string input;
  Portfolio portfolio;
  WatchList watchlist;
  
  init(portfolio);

  while (1)
  {
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Pick an option: ";
    cin >> input;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
  
    if (input == "q" || input == "quit" || input == "exit")
    {
      break;
    }
    // look up a stock price
    else if (input == "price")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;

      StockMarket market;
      Stock stock = market.fetchMarketData(symbol);
      cout << stock.symbol << " : $" << stock.price << endl;
    }
    // buy a stock for the portfolio
    else if (input == "buy")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;
      
      uint16_t numOfShares;
      cout << "How many shares: ";
      cin >> numOfShares;

      portfolio.buyStock(symbol, numOfShares);
    }
    // sell a stock from portfolio
    else if (input == "sell")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;
      
      uint16_t numOfShares;
      cout << "How many shares: ";
      cin >> numOfShares;
      
      portfolio.sellStock(symbol, numOfShares);
    }
    // view my portfolio
    else if (input == "view")
    {
      portfolio.printPortfolio();
    }
    // view my watchlist
    else if (input == "watch")
    {
      watchlist.printWatchList();
    }
    // add a stock to my watchlist
    else if (input == "add")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;

      watchlist.addSymbol(symbol);
    }
    // remove a stock to my watchlist
    else if (input == "remove")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;

      watchlist.removeSymbol(symbol);
    }
    else if (input == "help")
    {
      cout << "Available commands: " << endl;
      cout << "    price    - look up a stock price" << endl;
      cout << "    buy      - buy a stock for my portfolio" << endl;
      cout << "    sell     - sell a stock from my portfolio" << endl;
      cout << "    view     - view my portfolio" << endl;
      cout << "    watch    - view your watch list" << endl;
      cout << "    add      - add a stock to your watch list" << endl;
      cout << "    remove   - remove a stock to your watch list" << endl;
      cout << "    exit     - close the program" << endl;
    }
    else
    {
      
      cout << "Unknown command. say 'help' for more info." << endl;
    }
  }

  return 0;
}