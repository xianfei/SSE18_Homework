#pragma once
#include "shape.h"
#include "point.h"
#include<iostream>
#include<ostream>
static int cNum;
class Circle : public shape {
  int r=0;
  point* centerPoint = nullptr;

 public:

   double getArea();

   bool operator==(shape& s);

   shape& operator=(shape& s);

   int& operator[](int index);

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