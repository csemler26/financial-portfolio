#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <iomanip>
#include <iostream>
#include <curl/curl.h>
#include "json.h"
#include "dataTypes.h"

class StockMarket {
public:
  Stock fetchMarketData(const std::string& symbol);

private:
  static size_t formatDataCallback(void* contents, size_t size, size_t nmemb, void* userp);
  Stock parseData(const std::string& symbol, std::string& readBuffer);
};

#endif // MARKET_H