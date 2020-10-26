#pragma once
#include <om/SymbolContext.h>
#include "ModelParams.h"

struct Model
{
  void compute();
};

struct PosUpperLowerBoundModel : public Model
{
  void compute(const SymbolContext &sc)
  {
    const auto &bound = sc.getParam<PosUpperLowerBound>();
    double midpos = 0.5 * (bound.posUpperLimit + bound.posLowerLimit);
  }
};