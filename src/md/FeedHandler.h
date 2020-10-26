#pragma once
#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>
#include <functional>
#include "MDEvent.h"

struct FeedHandler
{
  typedef std::function<void(TradeEvent)> TradeEventCB;
  static map<std::string, TradeEventCB> callBacks;

  static void start()
  {
    BinaCPP_websocket::init();
    BinaCPP_websocket::connect_endpoint(ws_aggTrade_OnData, "/ws/bnbbtc@aggTrade");
    BinaCPP_websocket::enter_event_loop();
  }

  static bool subscribeTrade(std::string mdSymbol_, TradeEventCB cb_)
  {
    callBacks[mdSymbol_] = cb_;
    return true;
  }

  static int ws_aggTrade_OnData(Json::Value &json_result)
  {
    const auto& symbol = json_result["s"].asString();
    auto found = callBacks.find(symbol);
    if (found != callBacks.end())
    {
      std::cout << "found callback" << std::endl;
      TradeEvent te;
      te.tp = std::stof(json_result["p"].asString());
      te.ts = std::stof(json_result["q"].asString());
      found->second(te);
    }

    /*
    long aggTradeId = json_result["a"].asInt64();
    for (const auto &mbm : json_result.getMemberNames())
    {
      std::cout << "mbm: " << mbm << ", val: " << json_result[mbm].asString() << std::endl;
    }
    */
    
    return true;
  }

};