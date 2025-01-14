#include "portfolio.h"
#include "market.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Portfolio::Portfolio(Database& db) : db_(db)
{
  loadPortfolio();
}

Portfolio::~Portfolio()
{
  savePortfolio();
}

bool Portfolio::buyStock(string& symbol, uint16_t& numOfShares) 
{
  transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
  cout << "Buying " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << endl;

  Investment stockToBuy;
  StockMarket market;
  Stock tempStock = market.fetchMarketData(symbol);
  if (tempStock.symbol == "")
  {
    cerr << "Error: Unable to fetch market data for " << symbol << " stock" << endl;
    return -1;
  }
  else
  {
    stockToBuy.symbol = tempStock.symbol;
    stockToBuy.price = tempStock.price;
    stockToBuy.quantity = numOfShares;
  }

  // already own shares
  if (investments_.find(stockToBuy.symbol) != nullptr)
  {
    int previouslyOwned = investments_[stockToBuy.symbol].quantity;
    double previousPrice = investments_[stockToBuy.symbol].price;
    investments_[stockToBuy.symbol].price = ((previousPrice * previouslyOwned) + (stockToBuy.price * stockToBuy.quantity)) / (previouslyOwned + numOfShares);
    investments_[stockToBuy.symbol].quantity += stockToBuy.quantity;
  }
  // new investment
  else
  {
    investments_[stockToBuy.symbol] = stockToBuy;
    cout << "Successfully bought " << numOfShares << ((numOfShares == 1) ? " share of" : " shares of ") << symbol << endl;
  }
  savePortfolio();
  return 0;
}

bool Portfolio::sellStock(string& symbol, uint16_t& numOfShares)
{
  transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
  cout << "Selling " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << endl;

  auto it = investments_.find(symbol);
  if (it != nullptr)
  {
    if (it->second.quantity >= numOfShares) 
    {
      it->second.quantity -= numOfShares;
      std::cout << "Sold " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << std::endl;
      if (it->second.quantity == 0) 
      {
        investments_.erase(symbol);
      }
    }
    else 
    {
      std::cerr << "Error: Not enough shares of " << symbol << " to sell in portfolio." << std::endl;
      return -1;
    }
  }
  else
  {
    std::cerr << "Error: " << symbol << " not found in portfolio." << std::endl;
    return -1;
  }
  
  savePortfolio();
  return 0;
}

void Portfolio::printPortfolio()
{
  cout << "Your portfolio:" << endl;
  for (const auto& stockPair : investments_)
  {
    std::cout << "Symbol: " << stockPair.second.symbol
              << ", Quantity: " << stockPair.second.quantity
              << std::fixed << std::setprecision(2) 
              << ", Average Price: $" << stockPair.second.price << std::endl;
  }
}

void Portfolio::savePortfolio()
{
  cout << "Saving portfolio at " << PORTFOLIO_PATH << endl;

  ofstream outFile(PORTFOLIO_PATH);

  if (!outFile)
  {
    cerr << "Error saving portfolio: " << PORTFOLIO_PATH << endl;
    return;
  }

  for (const auto& investment : investments_)
  {
    outFile << investment.second.symbol << ":" << investment.second.quantity << ":" << investment.second.price << "\n";
  }

  outFile.close();
}

void Portfolio::loadPortfolio()
{
  if (!filesystem::exists(PORTFOLIO_PATH))
  {
    cerr << "File does not exist at " << PORTFOLIO_PATH << endl;
    return;
  }

  ifstream file(PORTFOLIO_PATH);
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      Investment newStock = parsePortfolio(line);
      investments_[newStock.symbol] = newStock;
    }

    file.close();
  }
  else
  {
    cerr << "Failed to open file: " << PORTFOLIO_PATH << endl;
  }
}

Investment Portfolio::parsePortfolio(string& line)
{
  const char delimiter = ':';
  Investment newStock;
  stringstream ss(line);

  string symbol;
  if (getline(ss, symbol, delimiter))
  {
    newStock.symbol = symbol;
  }

  string quantity;
  if (getline(ss, quantity, delimiter))
  {
    newStock.quantity = stoi(quantity);
  }

  string price;
  if (getline(ss, price, delimiter))
  {
    newStock.price = stod(price);
  }

  return newStock;
}
