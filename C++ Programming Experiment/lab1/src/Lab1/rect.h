#pragma once
#include "shape.h"
#include "point.h"

class rect : public shape {
  point upPoint;
  point downPoint;

 public:
  rect(point upPoint, point downPoint, color lineColor, color fillColor,
       bool isFilled);

  rect(point upPoint, point downPoint, color lineColor);

  void draw();

  rect() = default;

  void setUpPoint(point upPoint);

  void setDownPoint(point downPoint);

  point getUpPoint();

  point getDownPoint();
};
