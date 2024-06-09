#include "portfolio.h"
#include "market.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Portfolio::Portfolio()
{
  loadPortfolio();
}

Portfolio::~Portfolio()
{
  savePortfolio();
}

void Portfolio::buyStock(string& symbol, uint16_t& numOfShares) 
{
  transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
  cout << "Buying " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << endl;

  Stock newStock;
  StockMarket market;
  newStock = market.fetchMarketData(symbol);
  newStock.quantity = numOfShares;

  // already own shares
  if (stocks.find(newStock.symbol) != stocks.end())
  {
    int previouslyOwned = stocks[newStock.symbol].quantity;
    double previousPrice = stocks[newStock.symbol].price;
    stocks[newStock.symbol].price = ((previousPrice * previouslyOwned) + (newStock.price * newStock.quantity)) / (previouslyOwned + numOfShares);
    stocks[newStock.symbol].quantity += newStock.quantity;
  }
  // new investment
  else
  {
    stocks[newStock.symbol] = newStock;
    cout << "Successfully bought " << numOfShares << ((numOfShares == 1) ? " share of" : " shares of ") << symbol << endl;
  }
  savePortfolio();
}

void Portfolio::sellStock(string& symbol, uint16_t& numOfShares)
{
  transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
  cout << "Selling " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << endl;

  auto it = stocks.find(symbol);
  if (it != stocks.end() && it->second.quantity >= numOfShares) {
    it->second.quantity -= numOfShares;
    std::cout << "Sold " << numOfShares << ((numOfShares == 1) ? " share of " : " shares of " ) << symbol << std::endl;
    if (it->second.quantity == 0) {
      stocks.erase(it);
    }
  } else {
    std::cerr << "Error: Not enough shares to sell or stock not found in portfolio." << std::endl;
  }
  savePortfolio();
}

void Portfolio::printPortfolio()
{
  cout << "Your portfolio:" << endl;
  for (const auto& stockPair : stocks)
  {
    std::cout << "Symbol: " << stockPair.second.symbol
              << ", Quantity: " << stockPair.second.quantity
              << ", Average Price: " << stockPair.second.price << std::endl;
  }
}

void Portfolio::savePortfolio()
{
  cout << "Saving portfolio at " << portfolioPath << endl;

  ofstream outFile(portfolioPath);

  if (!outFile)
  {
    cerr << "Error saving portfolio: " << portfolioPath << endl;
    return;
  }

  for (const auto& investment : stocks)
  {
    outFile << investment.second.symbol << ":" << investment.second.quantity << ":" << investment.second.price << "\n";
  }

  outFile.close();
}

void Portfolio::loadPortfolio()
{
  if (!filesystem::exists(portfolioPath))
  {
    cerr << "File does not exist at " << portfolioPath << endl;
    return;
  }

  ifstream file(portfolioPath);
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      Stock newStock = parsePortfolio(line);
      stocks[newStock.symbol] = newStock;
    }

    file.close();
  }
  else
  {
    cerr << "Failed to open file: " << portfolioPath << endl;
  }
}

Stock Portfolio::parsePortfolio(string& line)
{
  const char delimiter = ':';
  Stock newStock;
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
