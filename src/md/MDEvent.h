#pragma once

enum MDType
{
  Trade
};

struct TradeEvent
{
  double tp;
  double ts;
};

struct L1Event
{
  double p;
  double s;
};