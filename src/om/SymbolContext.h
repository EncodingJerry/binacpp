#pragma once

#include <product/Product.h>
#include "ExchangeOrder.h"
#include <model/ModelParams.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <tuple>
#include "md/Book.h"

class SymbolContext;

const std::unordered_map<std::string, std::unique_ptr<SymbolContext>> &allSymbolContexts();
void initAllSymbolContexts(std::vector<Product> products_);
SymbolContext *findSymbolContext(const std::string &symbol_);

template <typename... T>
struct SymbolContextT
{
  std::tuple<T...> members;

  template <typename ParamTy>
  ParamTy &getParam()
  {
    return std::get<ParamTy>(members);
  };

  template <typename ParamTy>
  const ParamTy &getParam() const
  {
    return std::get<ParamTy>(members);
  };
};

class SymbolContext : public SymbolContextT<PosUpperLowerBound>
{
  Product _product;
  double _position;
  std::vector<ExchangeOrder> _openOrders;
  MD _marketData;

public:
  SymbolContext(Product product_) : _product(product_),
    _marketData(product_.tradeSymbol(), this)
  {
    _marketData.subscribeTrade();
  }

  double getCurrentPosition();
  void updatePosition(double delta);
};
