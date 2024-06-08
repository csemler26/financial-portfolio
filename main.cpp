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
    cout << "Available options: " << endl;
    cout << "    1. look up a stock price" << endl;
    cout << "    2. buy a stock for my portfolio" << endl;
    cout << "    3. sell a stock from my portfolio" << endl;
    cout << "    4. view my portfolio" << endl;
    cout << "Pick an option: ";
    cin >> input;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
  
    if (input == "q" || input == "quit" || input == "exit")
    {
      break;
    }
    // look up a stock price
    else if (input == "1")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;

      StockMarket market;
      Stock stock = market.fetchMarketData(symbol);
      cout << stock.symbol << " : " << stock.price << endl;
    }
    // buy a stock for the portfolio
    else if (input == "2")
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
    else if (input == "3")
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
    else if (input == "4")
    {      
      portfolio.printPortfolio();
    }
  }

  return 0;
}