#include "SymbolContext.h"

namespace hidden
{
  auto &__allSymbolContexts()
  {
    static std::unordered_map<std::string, std::unique_ptr<SymbolContext>> _allSymbolContexts;
    return _allSymbolContexts;
  }
} // namespace hidden

const std::unordered_map<std::string, std::unique_ptr<SymbolContext>> &allSymbolContexts()
{
  return hidden::__allSymbolContexts();
}

void initAllSymbolContexts(std::vector<Product> products_)
{
  for (const auto product : products_)
  {
    auto sc = std::make_unique<SymbolContext>(product);
    hidden::__allSymbolContexts().emplace(product.tradeSymbol(), std::move(sc));
  }
}

SymbolContext *findSymbolContext(const std::string &symbol_)
{
  auto ret = allSymbolContexts().find(symbol_);
  if (ret == allSymbolContexts().end())
  {
    return nullptr;
  }
  return ret->second.get();
}
