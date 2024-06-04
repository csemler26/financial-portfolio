#include <iostream>
#include <string>
#include <iomanip>
#include <curl/curl.h>
#include "include/json.h"

using namespace std;

// Function to write data from cURL to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
  string symbol;

  while (symbol != "quit" && symbol != "q" && symbol != "exit")
  {
    cout << "Enter stock symbol: ";
    cin >> symbol;
    cout << "You entered: " << symbol << endl;

    string apiKey = "OK2DWQE7VA4ZPGTH";
    string readBuffer;

    CURL* curl = curl_easy_init();
    if (curl) 
    {
      string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + apiKey;

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

      CURLcode res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
        cerr << "cURL error: " << curl_easy_strerror(res) << endl;
      }
      curl_easy_cleanup(curl);
    }
    else
    {
      cout << "darn";
    }

    // Parse JSON response
    try {
        auto jsonData = nlohmann::json::parse(readBuffer);
        string priceStr = jsonData["Global Quote"]["05. price"];
        double price = stod(priceStr);
        cout << "Stock: " << symbol << endl;
        cout << "Price: $" << fixed << setprecision(2) << price << endl;
    } catch (const exception& e) {
      cerr << "Failed to parse JSON: " << e.what() << endl;
    }    
  }

  return 0;
}