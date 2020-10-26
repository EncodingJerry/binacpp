#pragma once

struct PosUpperLowerBound
{
  bool ready = false;

  double ewma100 = 0.0;
  double ewma500 = 0.0;
  double ewma1000 = 0.0;

  double posUpperLimit = 0;
  double posLowerLimit = 0;
  double spread = 10.1;
  double buysellSkew = 0.0;
  double alphaMultiplier = 0.0;
  double positionSkew = 0.0;
};