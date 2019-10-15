#pragma once
#include <graphics.h>

class point {
 private:
  int x, y;

 public:
  point(int x, int y);

  point();

  point(const point& p);
  
  void draw(color_t c = CYAN);

  int getX();

  int getY();

  void setX(int x);

  void setY(int y);
};
