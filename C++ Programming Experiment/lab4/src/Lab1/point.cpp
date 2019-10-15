#include "point.h"


point::point(int x, int y) : x{x}, y{y} {};

point::point() = default;

point::point(const point& p) {
  this->x=p.x;
  this->y=p.y;
}

void point::draw(color_t c) { putpixel(x, y, c); }

int point::getX() { return x; }

int point::getY() { return y; }

void point::setX(int x) { point::x = x; }

void point::setY(int y) { point::y = y; }

point& point::operator+=(const point& p)
{
  // TODO: 在此处插入 return 语句
  this->x += p.x;
  this->y += p.y;
  return *this;
}

int& point::operator[](int index)
{
    if (index == 0) {
      return x;
    }
    else if (index == 1) {
      return y;
    }
    else throw std::out_of_range("point[] out of range");
}

bool point::operator!=(const point& p)
{
  if (this->x == p.x && this->y == p.y)return false;
  else return true;
}

bool point::operator==(const point& p)
{
  if (this->x == p.x && this->y == p.y)return true;
  else return false;
}

point& point::operator=(const point& p)
{
  this->x = p.x;
  this->y = p.y;
  return *this;
}

point point::operator+(const point& p)
{
  point p2;
  p2.setX((x + p.x) / 2);
  p2.setY((y + p.y) / 2);
  return p2;
}
