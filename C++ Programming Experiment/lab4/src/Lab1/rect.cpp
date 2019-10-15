#include "rect.h"


double rect::getArea()
{
  return ((*downPoint)[0]-(*upPoint)[0])*((*downPoint)[1] - (*upPoint)[1]);
}

bool rect::operator<(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  if (this->getArea() < r.getArea())return true;
  else 
  return false;
}

bool rect::operator<=(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  if (this->getArea() <= r.getArea())return true;
  else
    return false;
}

bool rect::operator>(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  if (this->getArea() > r.getArea())return true;
  else
    return false;
}

bool rect::operator>=(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  if (this->getArea() >= r.getArea())return true;
  else
    return false;
}

bool rect::operator==(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  for (int i = 0; i < 2; i++) {
    if ((*(this->downPoint))[i] != (*(r.downPoint))[i]) return false;
    if ((*(this->upPoint))[i] != (*(r.upPoint))[i]) return false;
  }
  for (int i = 0; i < 3; i++) {
    if ((*(this->fillColor))[i] != (*(r.fillColor))[i]) return false;
    if ((*(this->lineColor))[i] != (*(r.lineColor))[i]) return false;
  }
  if (this->isFilled != r.isFilled)return false;
  return true;
}

int& rect::operator[](int index)
{
  switch (index) {
  case 0:return (*upPoint)[0];
  case 1:return (*upPoint)[1];
  case 2:return (*downPoint)[0];
  case 3:return (*downPoint)[1];
  default:throw std::out_of_range("rect[] out of range");
  }
}

rect::rect(point upPoint, point downPoint, color lineColor, color fillColor,
           bool isFilled)
    : shape(lineColor, fillColor, isFilled) {
  this->upPoint = new point{upPoint};
  this->downPoint = new point{downPoint};
  rNum++;
}

rect::rect() {
  this->upPoint = new point;
  this->downPoint = new point;
  rNum++;
}

rect::rect(const rect& r) : shape(r) {
  this->upPoint = new point{*(r.upPoint)};
  this->downPoint = new point{*(r.downPoint)};
  rNum++;
}

shape& rect::operator=(shape& s)
{
  rect& r = dynamic_cast<rect&>(s);
  delete upPoint;
  delete downPoint;
  this->upPoint = new point{ *(r.upPoint) };
  this->downPoint = new point{ *(r.downPoint) };
  //rNum++;
  for (int i = 0; i < 3; i++) {
    (*(this->fillColor))[i] = (*(r.fillColor))[i];
    (*(this->lineColor))[i] = (*(r.lineColor))[i];
  }
  this->isFilled = r.getIsFilled();
  return *this;
}

rect::~rect() {
  delete upPoint;
  delete downPoint;
  rNum--;
}

rect::rect(point upPoint, point downPoint, color lineColor)
    : shape(lineColor, CYAN, false) {
  this->upPoint = new point{upPoint};
  this->downPoint = new point{downPoint};
  rNum++;
}
void rect::draw() {
  setcolor(getLineColor());
  if (getIsFilled()) {
    setfillcolor(getFillColor());
    bar((*upPoint)[0], (*upPoint)[1], (*downPoint)[0], (*downPoint)[1]);
  }
  rectangle(upPoint->getX(), upPoint->getY(), downPoint->getX(),
              downPoint->getY());
}

void rect::setUpPoint(point upPoint) { *(this->upPoint) = upPoint; }

void rect::setDownPoint(point downPoint) { *(this->downPoint) = downPoint; }

point rect::getUpPoint() { return *upPoint; }

point rect::getDownPoint() { return *downPoint; }