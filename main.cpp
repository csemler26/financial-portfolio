#include <iostream>
#include <string>
#include <iomanip>
#include <curl/curl.h>
#include "include/json.h"
#include "include/market.h"

using namespace std;

int main()
{
  string input;
  while (1)
  {
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "Pick an option: ";
    cin >> input;
  
    if (input == "q" || input == "quit" || input == "exit")
    {
      break;
    }
    else if (input == "1")
    {
      string symbol;
      cout << "Enter stock symbol: ";
      cin >> symbol;

      DataMarket market;
      market.fetchMarketData(symbol);
    }
  }

  return 0;
}