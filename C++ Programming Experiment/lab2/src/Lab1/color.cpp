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