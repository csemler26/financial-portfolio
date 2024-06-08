#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <curl/curl.h>
#include "include/json.h"
#include "include/market.h"
#include "include/portfolio.h"
#include "include/dataTypes.h"

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
      cout << stock.symbol << " : " << stock.price << endl;
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
    else if (input == "help")
    {
      cout << "Available commands: " << endl;
      cout << "    price    - look up a stock price" << endl;
      cout << "    buy      - buy a stock for my portfolio" << endl;
      cout << "    sell     - sell a stock from my portfolio" << endl;
      cout << "    view     - view my portfolio" << endl;
      cout << "    exit     - close the program" << endl;
    }
  }

  return 0;
}