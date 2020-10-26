#pragma once

#include "md/MDEvent.h"
#include "infra/Dispatcher.h"

Dispatcher<TradeEvent, L1Event> &getDispatcher();

class TradeEventHandler : public Handler<TradeEvent>,
                          public Handler<L1Event>
{
public:
  TradeEventHandler();

private:
  void handleEvent(TradeEvent) override
  {
    std::cout << "hello trade event" << std::endl;
  }

  void handleEvent(L1Event) override
  {
    std::cout << "hello L1Event" << std::endl;
  }
};
