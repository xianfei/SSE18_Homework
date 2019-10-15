#pragma once
#include "shape.h"
#include "point.h"
static int rNum;
class rect : public shape {
  point* upPoint = nullptr;
  point* downPoint = nullptr;

 public:
  rect(point upPoint, point downPoint, color lineColor, color fillColor,
       bool isFilled);

  rect(point upPoint, point downPoint, color lineColor);

  void draw();

  rect();

  rect(const rect& r);

  ~rect();

  void setUpPoint(point upPoint);

  void setDownPoint(point downPoint);

  point getUpPoint();

  point getDownPoint();
};
