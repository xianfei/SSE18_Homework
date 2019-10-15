#include "tria.h"

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
  p[0] = p1->getX();
  p[1] = p1->getY();
  p[2] = p2->getX();
  p[3] = p2->getY();
  p[4] = p3->getX();
  p[5] = p3->getY();
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
