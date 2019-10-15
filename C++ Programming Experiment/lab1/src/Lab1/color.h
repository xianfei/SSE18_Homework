#pragma once
#include <graphics.h>

class color {
  int r = 0, g = 0, b = 0;
  color_t c;

 public:
  color(int r, int g, int b) : r(r), g(g), b(b) { c = EGERGB(r, g, b); };

  color(color_t c) : c(c) {}

  color() = default;

  int getR();

  int getG();

  int getB();

  color_t getC();

  void setR(int r);

  void setG(int g);

  void setB(int b);

  void setC(color_t c);
};