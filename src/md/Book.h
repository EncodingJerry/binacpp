#pragma once

#include <array>
#include <cassert>
#include <vector>
#include <string>
#include "MDEvent.h"
#include "FeedHandler.h"
#include "om/Handler.h"

class SymbolContext;

enum class OrderSide : int
{
  Buy = 0,
  Sell = 1
};

enum class QuoteSide : int
{
  Bid = 0,
  Ask = 1,
  Invalid
};

struct Quote
{
  QuoteSide _side = QuoteSide::Invalid;
  int _size;
  double _price;
};

template <int MaxLevel = 10>
struct Book
{
  int levelCount = 0;
  std::array<Quote, MaxLevel> _quotes;
  const Quote& topQuote() const
  {
    assert(levelCount > 0);
    return _quotes[0];
  }
};

using OrderBook = Book<>;

struct MD
{
  std::string _mdSymbol = "";
  const SymbolContext* _sc = nullptr;
  // askBook, and bidBook
  OrderBook _books[2];

  MD(const std::string mdSymbol_, SymbolContext* sc_):_mdSymbol(mdSymbol_), _sc(sc_)
  {}

  void subscribeTrade()
  {
    std::cout << "subscribe trade" << std::endl;
    auto onTradeUpdate = [](TradeEvent te)
    {
      getDispatcher().dispatchEvent(te);
    };
    FeedHandler::subscribeTrade(_mdSymbol, onTradeUpdate);
  }

  void snapAll() const
  {
    // snap near
    // snap far
  }

  void snapFarSide(OrderSide ordSide_) const
  {
    auto& farBook = _books[getFarSideForOrder(ordSide_)];
    // snap farBook
  }

  template <QuoteSide qSide>
  const OrderBook& getBook() const
  {
    static_assert(QuoteSide::Bid == static_cast<QuoteSide>(0));
    static_assert(QuoteSide::Ask == static_cast<QuoteSide>(1));
    static_assert(qSide == QuoteSide::Ask || qSide == QuoteSide::Bid);
    return _books[static_cast<int>(qSide)];
  }

  const OrderBook& getFarSideBook(OrderSide ordSide_) const
  {
    return _books[getFarSideForOrder(ordSide_)];
  }

private:
  int getFarSideForOrder(OrderSide ordSide_) const
  {
    static_assert(QuoteSide::Bid == static_cast<QuoteSide>(0) &&
                  OrderSide::Buy == static_cast<OrderSide>(0));
    static_assert(QuoteSide::Ask == static_cast<QuoteSide>(1) &&
                  OrderSide::Sell == static_cast<OrderSide>(1));
    assert(ordSide_ == OrderSide::Buy || ordSide_ == OrderSide::Sell);
    return (static_cast<int>(ordSide_) + 1) & 1;
  }
};