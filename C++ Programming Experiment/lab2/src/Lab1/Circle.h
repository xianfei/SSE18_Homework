#pragma once
#include "shape.h"
#include "point.h"
static int cNum;
class Circle : public shape {
  int r=0;
  point* centerPoint = nullptr;

 public:
  Circle() ;

  Circle(const Circle& c);

  Circle(point centerPoint, int r, color lineColor, color fillColor,
         bool isFilled);

  Circle(point centerPoint, int r, color lineColor);

  ~Circle();

  void draw();

  void setR(int r);

  void setCenterPoint(point centerPoint);

  int getR();

  point getCenterPoint();
};