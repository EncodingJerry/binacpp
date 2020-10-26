#include <iostream>
#include "product/Product.h"
#include "om/SymbolContext.h"
#include "md/FeedHandler.h"
#include "om/Handler.h"
#include <thread>

using namespace std;

int main()
{
  auto products = getAllProducts();
  std::thread t1([]{FeedHandler::start();});

  initAllSymbolContexts(products);
  std::cout << "hello crypo currenty " << std::endl;
  std::cout << "found: " << findSymbolContext(products[0].tradeSymbol()) << std::endl;

  TradeEventHandler teh;
  std::cout << "jerry here" << std::endl;
  getDispatcher().startLoop();

  return 0;
}