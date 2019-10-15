#include "color.h"

color::color(int r, int g, int b) : r(r), g(g), b(b) { c = EGERGB(r, g, b); };

color::color(color_t c) : c(c) {}

color::color(const color& col) { 
  this->r = col.r;
  this->g = col.g;
  this->b = col.b;
  this->c = col.c;
}

int color::getR() { return r; }

int color::getG() { return g; }

int color::getB() { return b; }

color_t color::getC() { return c; }

void color::setR(int r) { color::r = r; }

void color::setG(int g) { color::g = g; }

void color::setB(int b) { color::b = b; }

void color::setC(color_t c) { color::c = c; }

bool color::operator==(const color& col)
{
  if (this->r == col.r &&
    this->g == col.g &&
    this->b == col.b &&
    this->c == col.c)return true;else 
  return false;
}

bool color::operator!=(const color& col)
{
  if (this->r == col.r &&
    this->g == col.g &&
    this->b == col.b &&
    this->c == col.c)return false; else
    return true;
}

color& color::operator=(const color& col)
{
  this->r = col.r;
  this->g = col.g;
  this->b = col.b;
  this->c = col.c;
  return *this;
  // TODO: 在此处插入 return 语句
}

int& color::operator[](int index)
{
  switch (index) {
  case 0:return r;
  case 1:return g;
  case 2:return b;
  default:throw std::out_of_range("color[] out of range");
  }
}
