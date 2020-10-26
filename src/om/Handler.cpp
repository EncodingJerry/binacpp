#include "Handler.h"

Dispatcher<TradeEvent, L1Event> &getDispatcher()
{
  static Dispatcher<TradeEvent, L1Event> di;
  return di;
}

TradeEventHandler::TradeEventHandler()
{
  std::cout << "ctor " << (void*)this << std::endl;
  getDispatcher().registerHandler<TradeEvent>(this);
  getDispatcher().registerHandler<L1Event>(this);
}
