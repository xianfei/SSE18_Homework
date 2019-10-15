#pragma once
#include <graphics.h>
#include <exception>
#include <stdexcept>

class point {
 private:
  int x=0, y=0;

 public:
  point(int x, int y);

  point();

  point(const point& p);
  
  void draw(color_t c = CYAN);

  int getX();

  int getY();

  void setX(int x);

  void setY(int y);

  point& operator+=(const point& p);

  int& operator[] (int index);

  bool operator!= (const point& p);

  bool operator== (const point& p);

  point& operator= (const point& p);

  point operator+ (const point& p);
};
