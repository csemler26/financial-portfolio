#include <algorithm>
#include <cctype>
#include "market.h"

using namespace std;

void DataMarket::fetchMarketData(std::string &symbol)
{
  string apiKey = "OK2DWQE7VA4ZPGTH";
  string readBuffer;

  CURL* curl = curl_easy_init();
  if (curl) 
  {
    string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + apiKey;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, formatDataCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      printData(symbol, readBuffer);
    }
    else
    {
      cerr << "cURL error: " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
  }
  else
  {
    cout << "darn";
  }
}

size_t DataMarket::formatDataCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t totalSize = size * nmemb;
  string* str = (string*)userp;
  str->append((char*)contents, totalSize);
  return totalSize;
}

void DataMarket::printData(string& symbol, string& readBuffer)
{
  try {
    auto jsonData = nlohmann::json::parse(readBuffer);
    string priceStr = jsonData["Global Quote"]["05. price"];
    double price = stod(priceStr);
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
    cout << "Stock: " << symbol << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
  } catch (const exception& e) {
    cerr << "Failed to parse JSON: " << e.what() << endl;
  }    
}
