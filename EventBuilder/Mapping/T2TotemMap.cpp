#include "T2TotemMap.hpp"
#include <TMath.h>

#include "./mapping/T2Mapping.map"



double dist(double x0, double y0, double x1, double y1)
{
  double distance;
  distance = TMath::Sqrt ( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1) );
  return distance;
}
