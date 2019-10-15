#pragma once
#include "shape.h"
#include "point.h"

static int tNum = 0;

class tria : public shape {
  point* p1 = nullptr;
  point* p2 = nullptr;
  point* p3 = nullptr;
  int p[6] = {0};
 public:
  tria();
  tria(const tria& t);
  tria(point p1, point p2, point p3, color lineColor, color fillColor=0,
       bool isFilled=false);
  ~tria();
  void draw();
  point getP1();
  point getP2();
  point getP3();
};
