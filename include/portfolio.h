#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <curl/curl.h>
#include "json.h"
#include "dataTypes.h"

const std::filesystem::path portfolioPath = "/var/financial-portfolio/portfolio.txt";

class Portfolio {
public:
  Portfolio();
  ~Portfolio();
  bool buyStock(std::string& symbol, uint16_t& numOfShares);
  bool sellStock(std::string& symbol, uint16_t& numOfShares);
  void printPortfolio();
  void savePortfolio();
  void loadPortfolio();

private:
  Investment parsePortfolio(std::string& line);

  std::unordered_map<std::string, Investment> investments_;
};

#endif // PORTFOLIO_H