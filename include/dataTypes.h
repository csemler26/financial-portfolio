#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

typedef struct stock_t {
  std::string symbol;
  int quantity;
  double price;
} Stock;

#endif // DATATYPES_H