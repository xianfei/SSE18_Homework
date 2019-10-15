#include "point.h"


point::point(int x, int y) : x{x}, y{y} {};

point::point() = default;

void point::draw(color_t c) { putpixel(x, y, c); }

int point::getX() { return x; }

int point::getY() { return y; }

void point::setX(int x) { point::x = x; }

void point::setY(int y) { point::y = y; }
