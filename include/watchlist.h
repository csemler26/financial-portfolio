#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <string>
#include <mutex>
#include <filesystem>
#include <curl/curl.h>
#include "json.h"
#include "dataTypes.h"
#include "database.h"
#include "market.h"

const std::filesystem::path WATCHLIST_PATH = "/var/financial-portfolio/watchlist.txt";

class Watchlist {
public:
  Watchlist(Database& db);
  ~Watchlist();
  
  /*  
   *  @brief Adds a stock symbol to the watchlist
   *
   *  @param symbol The stock symbol to add 
   */
  void addSymbol(const std::string& symbol);
  
  /*  
   *  @brief Removes a stock symbol to the watchlist
   *
   *  @param symbol The stock symbol to remove 
   */
  void removeSymbol(const std::string& symbol);
  
  /*  
   *  @brief Iterates through current watchlist and fetches updated stock prices
   */
  void updateStockPrices();
  
  /*  
   *  @brief Iterates through current watchlist and prints the last fetched stock prices
   */
  void printWatchList();
  
  /*  
   *  @brief Iterates through current watchlist and updates the SQL table with the last fetched stock prices
   *  @note This function will be removed when the SQL table is replaced with Rest API communication to the frontend
   */
  void updateSqlTableValues();

private:
  /*  
   *  @brief Updates the UnorderedMap with the stock symbols from the stored SQL table
   */
  void loadWatchlist();
  
  /*  
   *  @brief Makes a call to the Market class to fetch the latest stock price data
   *
   *  @param symbol The stock symbol to be used in API call 
   */
  Stock fetchStockData(const std::string& symbol);

  UnorderedMap<std::string, Stock> stocks_;
  std::mutex printMutex_;
  Database& db_;
};

#endif // WATCHLIST_H