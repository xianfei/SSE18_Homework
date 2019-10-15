#pragma once
#include "shape.h"
#include "point.h"
class Circle : public shape {
  int r;
  point centerPoint;

 public:
  Circle() = default;

  Circle(point centerPoint, int r, color lineColor, color fillColor,
         bool isFilled)
      : shape(lineColor, fillColor, isFilled), r(r), centerPoint(centerPoint) {}

  Circle(point centerPoint, int r, color lineColor)
      : shape(lineColor, CYAN, false), r(r), centerPoint(centerPoint) {}

  void draw();

  void setR(int r);

  void setCenterPoint(point centerPoint);

  int getR();

  point getCenterPoint();
};