#include "Product.h"

std::vector<Product> getAllProducts()
{
  const static std::vector<Product> products{
      {"BNBBTC"}};
  return products;
}
