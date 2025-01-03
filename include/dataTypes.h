#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

// Define USE_CUSTOM_DATA_STRUCTURES to use custom data structure classes (UltimateDSA)
// #define USE_CUSTOM_DATA_STRUCTURES
#ifdef USE_CUSTOM_DATA_STRUCTURES
#include "../UltimateDSA/include/vector.h"
#include "../UltimateDSA/include/unordered_map.h"

template<typename T>
using Vector = DSA::Vector<T>;

template<typename K, typename V>
using UnorderedMap = DSA::UnorderedMap<K, V>;

template<typename K>
using UnorderedSet = DSA::UnorderedSet<K>;

#else
#include <vector>
#include <unordered_map>
#include <unordered_set>

template<typename T>
using Vector = std::vector<T>;

template<typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template<typename K>
using UnorderedSet = std::unordered_set<K>;

#endif

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