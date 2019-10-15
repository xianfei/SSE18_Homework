#include "color.h"


  int color::getR() { return r; }

int color::getG() { return g; }

int color::getB() { return b; }

color_t color::getC() { return c; }

void color::setR(int r) { color::r = r; }

void color::setG(int g) { color::g = g; }

void color::setB(int b) { color::b = b; }

void color::setC(color_t c) { color::c = c; }