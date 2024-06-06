#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <iomanip>
#include <iostream>
#include <curl/curl.h>
#include "json.h"

class DataMarket {
public:
  void fetchMarketData(std::string& symbol);

private:
  static size_t formatDataCallback(void* contents, size_t size, size_t nmemb, void* userp);
  void printData(std::string& symbol, std::string& readBuffer);
};

#endif // PORTFOLIO_H