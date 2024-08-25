#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <curl/curl.h>
#include "include/json.h"
#include "include/market.h"
#include "include/portfolio.h"
#include "include/dataTypes.h"
#include "include/watchlist.h"
#include "include/database.h"

using namespace std;

// Helper function to trim spaces and quotes
std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(' ');
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

// Function to load environment variables from a .env file
void load_env_file(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Could not open .env file" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    // Ignore empty lines and comments
    if (line.empty() || line[0] == '#') continue;

    size_t delimiter_pos = line.find('=');
    if (delimiter_pos == std::string::npos) continue;

    std::string key = trim(line.substr(0, delimiter_pos));
    std::string value = trim(line.substr(delimiter_pos + 1));

    // Remove any quotes around the value
    if (value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2);
    }

    // Set the environment variable (on POSIX systems)
    setenv(key.c_str(), value.c_str(), 1);
  }
  file.close();
}

void init(Portfolio& portfolio)
{
  portfolio.loadPortfolio();
  // portfolio.printPortfolio();
  load_env_file(".env");
}

int main()
{
  string input;
  Portfolio portfolio;
  Watchlist watchlist;
  Database db("financial_portfolio.db");
  
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
    // open database
    else if (input == "db" || input == "database")
    {
      if (db.executeScript("database/createTables.sql")) 
      {
        cout << "Tables created successfully." << endl;
      } 
      else 
      {
        cerr << "Failed to create tables." << endl;
      }
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