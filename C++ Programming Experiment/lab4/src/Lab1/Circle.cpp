#include "Circle.h"

Circle::~Circle() { 
  delete centerPoint;
  cNum--; 
}

double Circle::getArea()
{
  return 3.1415*r*r;
}

bool Circle::operator==(shape& s)
{
  Circle& r = dynamic_cast<Circle&>(s);
  for (int i = 0; i < 2; i++) {
    if ((*(this->centerPoint))[i] != (*(r.centerPoint))[i]) return false;
  }
  for (int i = 0; i < 3; i++) {
    if ((*(this->fillColor))[i] != (*(r.fillColor))[i]) return false;
    if ((*(this->lineColor))[i] != (*(r.lineColor))[i]) return false;
  }
  if (this->isFilled != r.isFilled)return false;
  return true;
}

shape& Circle::operator=(shape& s)
{
  Circle& c = dynamic_cast<Circle&>(s);
  for (int i = 0; i < 2; i++) {
    (*(this->centerPoint))[i] = (*(c.centerPoint))[i];
  }
  for (int i = 0; i < 3; i++) {
    (*(this->fillColor))[i] = (*(c.fillColor))[i];
    (*(this->lineColor))[i] = (*(c.lineColor))[i];
  }
  this->r = c.getR();
  isFilled = c.getIsFilled();
  return *this;
}

int& Circle::operator[](int index)
{
  switch (index) {
  case 0:return (*centerPoint)[0];
  case 1:return (*centerPoint)[1];
  case 2:return r;
  default:throw std::out_of_range("rect[] out of range");
  }
  // TODO: 在此处插入 return 语句
}

Circle::Circle() {
  this->centerPoint = new point{0,0};
  cNum++; 
};

Circle::Circle(const Circle& c) :shape(c){
  this->centerPoint = new point{*(c.centerPoint)};
  cNum++;
}

Circle::Circle(point centerPoint, int r, color lineColor, color fillColor,
       bool isFilled)
    : shape(lineColor, fillColor, isFilled), r(r) {
  this->centerPoint = new point{centerPoint};
  cNum++;
}

Circle::Circle(point centerPoint, int r, color lineColor)
    : shape(lineColor, CYAN, false), r(r){
  this->centerPoint = new point{centerPoint};
  cNum++;
}

void Circle::draw() {
    setcolor(getLineColor());
    if (getIsFilled()) {
      setfillcolor(getFillColor());
      fillellipse(centerPoint->getX(), centerPoint->getY(), r, r);
    } else
    circle(centerPoint->getX(), centerPoint->getY(), r); 
  }


void Circle::setR(int r) {
    Circle::r = r;
  }

void Circle::setCenterPoint(point centerPoint) {
  *(this->centerPoint) = centerPoint;
  }

int Circle::getR() { return r; }

point Circle::getCenterPoint() { return *centerPoint; }
