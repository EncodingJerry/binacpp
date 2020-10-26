
#pragma once

#include <string>
#include <vector>

class Product
{
  std::string _symbol;

public:
  Product(std::string sym_) : _symbol(sym_)
  {
  }

  const std::string &tradeSymbol() const
  {
    return _symbol;
  }
};

std::vector<Product> getAllProducts();
