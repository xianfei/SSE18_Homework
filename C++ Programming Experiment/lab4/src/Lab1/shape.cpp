#include "shape.h"


shape::shape(color lineColor, color fillColor, bool isFilled):isFilled(isFilled) {
  this->lineColor = new color{lineColor};
  this->fillColor = new color{fillColor};
}

shape::shape() : isFilled(false) {
  this->lineColor = new color{0};
  this->fillColor = new color{0};
}

shape::~shape(){
  delete lineColor;
  lineColor = nullptr;
  delete fillColor;
  fillColor = nullptr;
}

shape::shape(const shape& s) :isFilled(s.isFilled) {
  this->lineColor = new color{*(s.lineColor)};
  this->fillColor = new color{*(s.fillColor)};
}

bool shape::operator<(shape& r)
{
  if (this->getArea() < r.getArea())return true;
  else
    return false;
}

bool shape::operator<=(shape& r)
{
  if (this->getArea() <= r.getArea())return true;
  else
    return false;
}

bool shape::operator>(shape & r)
{
  if (this->getArea() > r.getArea())return true;
  else
    return false;
}

bool shape::operator>=(shape & r)
{
 // rect& r = dynamic_cast<rect&>(s);
  if (this->getArea() >= r.getArea())return true;
  else
    return false;
}

bool shape::getIsFilled() { return isFilled; }

color_t shape::getLineColor() { return lineColor->getC(); }

color_t shape::getFillColor() { return fillColor->getC(); }

void shape::setLineColor(color lineColor) { *(this->lineColor) = lineColor; }

void shape::setFillColor(color fillColor) { *(this->fillColor) = fillColor; }

void shape::setIsFilled(bool isFilled) { shape::isFilled = isFilled; }

