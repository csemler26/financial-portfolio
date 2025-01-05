#include <algorithm>
#include <cctype>
#include "market.h"

using namespace std;

Stock StockMarket::fetchMarketData(const std::string& symbol)
{
  Stock output;
  const char* api_key = std::getenv("API_KEY");
  string readBuffer;

  CURL* curl = curl_easy_init();
  if (curl) 
  {
    string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + api_key;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, formatDataCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      output = parseData(symbol, readBuffer);
    }
    else
    {
      cerr << "cURL error: " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
  }

  return output;
}

size_t StockMarket::formatDataCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t totalSize = size * nmemb;
  string* str = (string*)userp;
  str->append((char*)contents, totalSize);
  return totalSize;
}

Stock StockMarket::parseData(const string& symbol, string& readBuffer)
{
  Stock output;
  string symbolUpper;
  symbolUpper.resize(symbol.size());
  transform(symbol.begin(), symbol.end(), symbolUpper.begin(), ::toupper);
  output.symbol = symbolUpper;

  try 
  {
    auto jsonData = nlohmann::json::parse(readBuffer);

    // Check if the key exists and is not null
    if (jsonData.contains("Global Quote") && !jsonData["Global Quote"].is_null() &&
        jsonData["Global Quote"].contains("05. price") && !jsonData["Global Quote"]["05. price"].is_null()) 
    {
      string priceStr = jsonData["Global Quote"]["05. price"];
      double price = stod(priceStr);

      output.price = price;
    } 
    else 
    {
      // cerr << "Price data not found in JSON response - max API calls used" << endl;
    }
  } 
  catch (const exception& e) 
  {
    cerr << "Failed to parse JSON: " << e.what() << endl;
  }    

  return output;
}
