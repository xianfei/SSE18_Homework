#include "tria.h"
#include <cmath>

double tria::getArea()
{
  return abs(0.5 * ((*p1)[0]* (*p2)[1] + (*p2)[0]* (*p3)[1] + (*p3)[0]* (*p1)[1] - (*p1)[0]* (*p3)[1] - (*p2)[0]* (*p1)[1] - (*p3)[0]* (*p2)[1]));
}

shape& tria::operator=(shape& s)
{
  tria& r = dynamic_cast<tria&>(s);
  for (int i = 0; i < 2; i++) {
    (*(this->p1))[i] = (*(r.p1))[i];
    (*(this->p2))[i] = (*(r.p2))[i];
    (*(this->p3))[i] = (*(r.p3))[i];
  }
  for (int i = 0; i < 3; i++) {
    (*(this->fillColor))[i] != (*(r.fillColor))[i];
    (*(this->lineColor))[i] != (*(r.lineColor))[i];
  }
  this->isFilled = r.isFilled;
  return *this;
}

bool tria::operator==(shape& s)
{
  tria& r = dynamic_cast<tria&>(s);
  for (int i = 0; i < 2; i++) {
    if ((*(this->p1))[i] != (*(r.p1))[i]) return false;
    if ((*(this->p2))[i] != (*(r.p2))[i]) return false;
    if ((*(this->p3))[i] != (*(r.p3))[i]) return false;
  }
  for (int i = 0; i < 3; i++) {
    if ((*(this->fillColor))[i] != (*(r.fillColor))[i]) return false;
    if ((*(this->lineColor))[i] != (*(r.lineColor))[i]) return false;
  }
  if (this->isFilled != r.isFilled)return false;
  return true;
}

int& tria::operator[](int index)
{
  switch (index) {
  case 0:return (*p1)[0];
  case 1:return (*p1)[1];
  case 2:return (*p2)[0];
  case 3:return (*p2)[1];
  case 4:return (*p3)[0];
  case 5:return (*p3)[1];
  default:throw std::out_of_range("rect[] out of range");
  }
  // TODO: 在此处插入 return 语句
}

tria::tria() {
  tNum++; 
  this->p1 = new point;
  this->p2 = new point;
  this->p3 = new point;
}

tria::tria(point p1, point p2, point p3, color lineColor, color fillColor,
           bool isFilled): shape(lineColor, fillColor, isFilled) {
  tNum++; 
  this->p1 = new point{p1};
  this->p2 = new point{p2};
  this->p3 = new point{p3};
}

tria::tria(const tria& t) {
  tNum++;
  this->p1 = new point{*(t.p1)};
  this->p2 = new point{*(t.p2)};
  this->p3 = new point{*(t.p3)};
}

tria::~tria() {
  delete p1;
  delete p2;
  delete p3;
  tNum--;
}

void tria::draw() { 
  p[0] = (*p1)[0];
  p[1] = (*p1)[1];
  p[2] = (*p2)[0];
  p[3] = (*p2)[1];
  p[4] = (*p3)[0];
  p[5] = (*p3)[1];
  setcolor(getLineColor());
  if (getIsFilled()) {
    setfillcolor(getFillColor());
    fillpoly(3,p);
  } else
    drawpoly(3, p);
}

point tria::getP1() { return *p1; }
point tria::getP2() { return *p2; }
point tria::getP3() { return *p3; }
