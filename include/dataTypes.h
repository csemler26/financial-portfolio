#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

typedef struct stock_t {
  std::string symbol;
  std::string name;
  double price;
} Stock;

typedef struct investment_t {
  std::string symbol;
  int quantity;
  double price;
} Investment;

#endif // DATATYPES_H